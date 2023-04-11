/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:47:28 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/11 11:57:34 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	ft_time_print(t_philo *philo)
{
	return (ft_calculate_time() - philo->start);
}

void	ft_write(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->write);
	printf("%lld %i %s\n", ft_time_print(philo),
		philo->who_am_i, action);
	pthread_mutex_unlock(philo->write);
}
