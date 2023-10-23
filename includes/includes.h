/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cypher <cypher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:48:12 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 23:20:43 by cypher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# define _XOPEN_SOURCE 600
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

typedef struct data
{
	int	n_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_time_to_eat;
}				t_data;

typedef struct philosophers
{
	int		id;
	int		eat_n_time;
	bool	able_to_eat;
}				t_philo;

typedef struct holder
{
	t_data	*data;
	t_philo	*philo;
	int		i;
	int		*fork;
	pthread_mutex_t general_mutex;
	pthread_mutex_t *fork_mutex;
} t_holder;


int		ft_atoi(char *str);
void	valid_args(int ac, char **av);
t_data	*data_init(int ac, char **av);
t_philo	*philo_init(t_data *data);
void	*ft_calloc(size_t nmemb, size_t size);
void	monitor(int ac, char **av);

#endif