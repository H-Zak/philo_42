/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:16:08 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/11 14:10:38 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	monitoring(t_philo **philo, int i)
{
	while (philo[1]->start > ft_calculate_time())
		usleep(20);
	while (*philo[1]->isdead != 1)
	{
		pthread_mutex_lock(philo[++i]->last_eat);
		if (philo[i]->nb_eat == 0)
			return (pthread_mutex_unlock(philo[i]->last_eat));
		if (ft_calculate_time() - philo[i]->time_last_eat >= philo[i]->time_die)
		{
			pthread_mutex_unlock(philo[i]->last_eat);
			pthread_mutex_lock(philo[i]->dead);
			*philo[i]->isdead = 1;
			ft_write(philo[i], "died");
			pthread_mutex_unlock(philo[i]->dead);
			break ;
		}
		pthread_mutex_unlock(philo[i]->last_eat);
		if (i == philo[1]->nb_philo)
			i = 0;
		usleep(1);
	}
	return (0);
}

void	end(t_philo **philo, int nb_philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo[1]->dead);
	free(philo[1]->dead);
	pthread_mutex_destroy(philo[1]->write);
	free(philo[1]->write);
	free(philo[1]->isdead);
	free(philo[1]->thread);
	pthread_mutex_destroy(philo[1]->last_eat);
	free(philo[1]->last_eat);
	while (++i <= nb_philo)
		pthread_mutex_destroy(&philo[1]->forks[i]);
	free(philo[1]->forks);
	i = 1;
	while (i <= nb_philo)
		free(philo[i++]);
	free(philo);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_philo			**philo;
	long long		time;
	int				i;

	time = ft_calculate_time() + 200;
	if (check_args(argc, argv) == 1)
		return (1);
	ft_one_philo(&argv[1]);
	philo = NULL;
	philo = init_thread(philo, argv);
	i = 1;
	while (i <= ft_atoi(argv[1]))
		philo[i++]->start = time;
	i = 0;
	while (++i <= ft_atoi(argv[1]))
		pthread_create(&philo[i]->thread[i], NULL, ft_routine, philo[i]);
	monitoring(philo, 0);
	i = 0;
	while (++i <= philo[1]->nb_philo)
		pthread_join(philo[i]->thread[i], NULL);
	end(philo, ft_atoi(argv[1]));
	return (0);
}
