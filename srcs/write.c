/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:47:28 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/03 18:27:26 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	ft_time_print(t_philo *philo)
{
	return (ft_calculate_time() - philo->start);
}

void	ft_write(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->write);
	printf("%lld : %i %s\n", ft_time_print(philo),
		philo->who_am_i, action);
	pthread_mutex_unlock(philo->write);
}
