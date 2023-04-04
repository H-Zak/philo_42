/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:14:43 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/04/04 17:43:17 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb_philo;
	long long int	start;
	long long int	time_die;
	long long int	time_eat;
	long long int	time_sleep;
	int				nb_eat;
	int				who_am_i;
	short int		*isdead;
	long long int	time_last_eat;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_eat;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*write;
}				t_philo;

int				check_args(int argc, char **argv);
void			s_fd(char *s, int fd);
int				ft_atoi(const char *nptr);
void			init_struct(t_philo *philo, char **argv, int i);
void			ft_one_philo(char **args);
t_philo			**init_thread(t_philo **philo, char **argv);
long long int	ft_calculate_time(void);
void			*ft_routine(void *p);
void			ft_write(t_philo *philo, char *action);
int				is_it_dead(t_philo *philo, int forks);
void			unlock_even(t_philo *philo, int forks);
void			end(t_philo **philo, int nb_philo);
int				odd(t_philo *philo);
int				even(t_philo *philo);
int				ft_atoi(const char *nptr);
t_philo			**init_thread(t_philo **philo, char **argv);
void			initialisation_mutex(t_philo **philo, int i);
void			unlock_odd(t_philo *philo, int forks);
void			unlock_even(t_philo *philo, int forks);

#endif
