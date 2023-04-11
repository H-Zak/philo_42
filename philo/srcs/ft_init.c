/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:25:47 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/11 14:15:20 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_struct(t_philo *philo, char **argv, int i)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		philo->nb_eat = ft_atoi(argv[5]);
	else
		philo->nb_eat = -1;
	philo->who_am_i = i;
	philo->time_last_eat = ft_calculate_time();
}

void	ft_one_philo(char **argv)
{
	if (ft_atoi(argv[0]) != 1)
		return ;
	printf("0 : 1 has taken his right fork\n\n");
	usleep(ft_atoi(argv[1]) * 1000);
	printf("%i : 1 died\n\n", ft_atoi(argv[1]));
	exit (0);
}

void	fill_1(t_philo **philo, pthread_mutex_t *fork,
	pthread_mutex_t *dead, pthread_mutex_t *write)
{
	int	i;

	i = 0;
	while (++i <= philo[1]->nb_philo)
	{
		philo[i]->forks = fork;
		philo[i]->dead = dead;
		philo[i]->write = write;
	}
}

void	fill_2(t_philo **philo, pthread_mutex_t *last_eat, short int *isdead)
{
	int	i;

	i = 0;
	while (++i <= philo[1]->nb_philo)
	{
		philo[i]->last_eat = last_eat;
		philo[i]->isdead = isdead;
	}
}

void	initialisation_mutex(t_philo **philo, int i)
{
	philo[1]->forks = malloc(sizeof(pthread_mutex_t)
			* (philo[1]->nb_philo + 1));
	philo[1]->write = malloc(sizeof(pthread_mutex_t));
	philo[1]->dead = malloc(sizeof(pthread_mutex_t));
	philo[1]->last_eat = malloc(sizeof(pthread_mutex_t));
	philo[1]->isdead = malloc(sizeof (short int));
	if (!philo[1]->forks || !philo[1]->write || !philo[1]->dead
		|| !philo[1]->last_eat || !philo[1]->isdead)
		end(philo, philo[i]->nb_philo);
	*philo[1]->isdead = 0;
	pthread_mutex_init(philo[1]->write, NULL);
	pthread_mutex_init(philo[1]->last_eat, NULL);
	pthread_mutex_init(philo[1]->dead, NULL);
	while (++i <= philo[1]->nb_philo)
		pthread_mutex_init(&philo[1]->forks[i], NULL);
	fill_1(philo, philo[1]->forks, philo[1]->dead, philo[1]->write);
	fill_2(philo, philo[1]->last_eat, philo[1]->isdead);
}
