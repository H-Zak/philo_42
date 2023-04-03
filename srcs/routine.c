/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:23 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/03 18:27:13 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* a quoi correspond le p et le premier usleep*/

void	eating(t_philo *philo)
{
	if (philo->who_am_i % 2 == 1)
		odd(philo);
	else
		even(philo);
	if (is_it_dead(philo, 0) != 1)
		return ;
	pthread_mutex_lock(philo->last_eat);
	philo->nb_eat--;
	philo->time_last_eat = ft_calculate_time();
	pthread_mutex_unlock(philo->last_eat);
	ft_write(philo, "is eating");
	usleep(philo->time_eat * 1000);
	if (is_it_dead(philo, 2) != 1)
		return ;
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->who_am_i]);
	if (philo->who_am_i == 1)
		pthread_mutex_unlock(&philo->forks[philo->nb_philo]);
	else
		pthread_mutex_unlock(&philo->forks[philo->who_am_i - 1]);
	ft_write(philo, " is sleeping");
	usleep(philo->time_sleep * 1000);
	if (is_it_dead(philo, 0) != 1)
		return ;
}

void	thinking(t_philo *philo)
{
	if (is_it_dead(philo, 0) == 0)
		return ;
	ft_write(philo, "is thinking");
}

void	*ft_routine(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->last_eat);
	philo->time_last_eat = ft_calculate_time() + philo->time_die;
	pthread_mutex_unlock(philo->last_eat);
	usleep((philo->nb_philo + philo->who_am_i) * 1000);
	while (philo->nb_eat != 0)
	{
		eating(philo);
		if (*philo->isdead == 1)
			return (NULL);
		if (philo->nb_eat == 0)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	unlock_even(philo, 2);
	return (NULL);
}
