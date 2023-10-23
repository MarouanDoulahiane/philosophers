/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:48:12 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 15:46:03 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>

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
	int	id;
	int	eat_n_time;
}				t_philo;

int		ft_atoi(char *str);
void	valid_args(int ac, char **av);
t_data	*data_init(int ac, char **av);
t_philo	*philo_init(t_data *data);
void	*ft_calloc(size_t nmemb, size_t size);

#endif