/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:23:40 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/03 08:24:26 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				eat_count;
	long			start_time;
	long			last_meal;
	int				id;
	pthread_mutex_t	forks;
	pthread_mutex_t	*data;
	pthread_mutex_t	*print;
	struct s_philo	*next;
}				t_philo;

long	get_time(void);
bool	ft_isdigit(int c);
void	*routine(void *arg);
void	ft_usleep(long time);
int		ft_atoi(const char *str);
void	free_philo(t_philo *philo);
void	initialize_mutex(t_philo **philo);
bool	check_valid_args(int ac, char **av);
void	push_back(t_philo **philo, t_philo *new);
void	initialize_philo(t_philo **philo, int ac, char **av);
t_philo	*new_philo(int id, int ac, char **av);

#endif