/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:22:43 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/04/03 18:24:07 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	j = 1;
	num = 0;
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		j = -1;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	return (num * j);
}

long long int	ft_calculate_time(void)
{
	struct timeval	timeofday;
	long long int	time;

	gettimeofday(&timeofday, NULL);
	time = (((timeofday.tv_sec % 100000) * 1000) + (timeofday.tv_usec / 1000));
	return (time);
}

t_philo	**init_thread(t_philo **philo, char **argv)
{
	int			i;
	pthread_t	*thread;

	i = 0;
	philo = malloc (sizeof(t_philo *) * (ft_atoi(argv[1]) + 1));
	thread = malloc(sizeof(pthread_t) * (ft_atoi(argv[1]) + 1));
	if (!philo || !thread)
		end(philo, philo[i]->nb_philo);
	i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		philo[i] = malloc(sizeof(t_philo));
		init_struct(philo[i], argv, i);
		philo[i]->thread = thread;
		i++;
	}
	initialisation_mutex(philo, 0);
	return (philo);
}
