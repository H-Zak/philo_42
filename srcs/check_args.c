/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:12:36 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/04 14:27:00 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void	s_fd(char *s, int fd)
{
	int			len;
	const void	*buf;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	buf = s;
	write(fd, buf, len);
}

int	check_number_of_philo(char *tab)
{
	int	i;

	i = 0;
	if (!tab || tab[i] == 0)
		return (1);
	while (tab && tab[i])
	{
		if (tab[i] < '0' || tab[i] > '9')
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_zero(char **argv)
{
	int	i;

	i = 1;
	while (argv && argv[i])
	{
		if (!argv || argv[i] == 0)
			return (1);
		if (ft_atoi(argv[i]) == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (s_fd("wrong_number of arguement", 2), 1);
	if (check_number_of_philo(argv[1]) == 1)
		return (s_fd("something is wrong with the number of _philo", 2), 1);
	if (check_number_of_philo(argv[2]) == 1)
		return (s_fd("something is wrong with the time_to_die", 2), 1);
	if (check_number_of_philo(argv[3]) == 1)
		return (s_fd("something is wrong with the time_to_eat", 2), 1);
	if (check_number_of_philo(argv[4]) == 1)
		return (s_fd("something is wrong with the time_to_sleep", 2), 1);
	if (argc == 6 && check_number_of_philo(argv[5]) == 1)
		return (s_fd("the number of times philo eat is wrong", 2), 1);
	if (check_zero(argv) == 1)
		return (s_fd("what can you do with 0s or no one ?", 2), 1);
	return (0);
}
