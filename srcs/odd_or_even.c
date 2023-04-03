/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_or_even.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:31:26 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/03 18:27:49 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_odd(t_philo *philo, int forks)
{
	if (forks >= 1)
	{
		if (philo->who_am_i == 1)
			pthread_mutex_unlock(&philo->forks[philo->nb_philo]);
		else
			pthread_mutex_unlock(&philo->forks[philo->who_am_i - 1]);
	}
	if (forks > 1)
		pthread_mutex_unlock(&philo->forks[philo->who_am_i]);
}

void	unlock_even(t_philo *philo, int forks)
{
	if (forks >= 1)
		pthread_mutex_unlock(&philo->forks[philo->who_am_i]);
	if (forks > 1)
	{
		if (philo->who_am_i == 1)
			pthread_mutex_unlock(&philo->forks[philo->nb_philo]);
		else
			pthread_mutex_unlock(&philo->forks[philo->who_am_i - 1]);
	}
}

int	is_it_dead(t_philo *philo, int forks)
{
	pthread_mutex_lock(philo->dead);
	if (*philo->isdead == 1)
	{
		if (philo->who_am_i % 2 == 1)
			unlock_odd(philo, forks);
		else
			unlock_even(philo, forks);
		pthread_mutex_unlock(philo->dead);
		return (0);
	}
	pthread_mutex_unlock(philo->dead);
	return (1);
}

void	even(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->who_am_i]);
	if (is_it_dead(philo, 1) != 1)
		return ;
	ft_write(philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->who_am_i - 1]);
	if (is_it_dead(philo, 2) != 1)
		return ;
	ft_write(philo, "has taken a fork");
}

void	odd(t_philo *philo)
{
	if (philo->who_am_i == 1)
		pthread_mutex_lock(&philo->forks[philo->nb_philo]);
	else
		pthread_mutex_lock(&philo->forks[philo->who_am_i - 1]);
	if (is_it_dead(philo, 1) != 1)
		return ;
	ft_write(philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->who_am_i]);
	if (is_it_dead(philo, 2) != 1)
		return ;
	ft_write(philo, "has taken a fork");
}
