/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:23 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/11 16:16:51 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_philo *philo)
{
	if (philo->who_am_i % 2 == 1)
	{
		if (odd(philo) == 9)
			return (9);
	}
	else
	{
		if (even(philo) == 9)
			return (9);
	}
	if (is_it_dead(philo, 2) != 1)
		return (9);
	pthread_mutex_lock(philo->last_eat);
	philo->nb_eat--;
	philo->time_last_eat = ft_calculate_time();
	pthread_mutex_unlock(philo->last_eat);
	ft_write(philo, "is eating");
	ft_usleep(philo->time_eat);
	if (is_it_dead(philo, 2) != 1)
		return (9);
	return (0);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->who_am_i]);
	if (philo->who_am_i == 1)
		pthread_mutex_unlock(&philo->forks[philo->nb_philo]);
	else
		pthread_mutex_unlock(&philo->forks[philo->who_am_i - 1]);
	if (is_it_dead(philo, 0) != 1)
		return ;
	ft_write(philo, "is sleeping");
	ft_usleep(philo->time_sleep);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_calculate_time();
	while (ft_calculate_time() - time < ms)
		usleep(100);
}

void	thinking(t_philo *philo)
{
	//peut etre utiliser le usleep de temps donner
	if (is_it_dead(philo, 0) == 0)
		return ;
	ft_write(philo, "is thinking");
	if(philo->nb_philo % 2 == 1)
		ft_usleep(1);
	// if (philo->time_eat >= philo->time_sleep)
	// {
	// 	ft_usleep(1);
	// }
	// else
	// {
	// 	ft_usleep(1);
	// }
	// if (philo->time_eat > philo->time_sleep)
	// {
	// 	ft_usleep((philo->time_eat) - (philo->time_sleep) + 1);
	// }
	// else
	// {
	// 	ft_usleep((philo->time_sleep) - (philo->time_eat) + 1);
	// }
}

void	*ft_routine(void *p)//provoquer un dernier tour de table 
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (philo->start > ft_calculate_time())
		ft_usleep(20);
	if (philo->who_am_i % 2 == 0)
		ft_usleep(philo->time_eat / 2);
	pthread_mutex_lock(philo->last_eat);
	philo->time_last_eat = philo->start;
	// philo->time_last_eat = ft_calculate_time() + philo->time_die;
	pthread_mutex_unlock(philo->last_eat);
	// usleep((philo->nb_philo + philo->who_am_i) * 1000);
	while (philo->nb_eat != 0)//regarde comment les autres font quand il y a un nombre de repas a faire, comment il tue leur philo, peut etre rajouter un ou deux repas de plus a faire
	{
		if (eating(philo) == 9)
			return (NULL);
		if (is_it_dead(philo, 2) != 1)
			return (NULL);
		if (philo->nb_eat == 0)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	if (philo->who_am_i % 2 == 1)
		unlock_odd(philo, 2);
	else
		unlock_even(philo, 2);
	return (NULL);
}
