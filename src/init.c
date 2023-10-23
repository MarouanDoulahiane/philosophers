/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 04:59:48 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 15:48:07 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

t_data	*data_init(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_time_to_eat = ft_atoi(av[5]);
	else
		data->n_time_to_eat = -1;
	return (data);
}

t_philo	*philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philosophers);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->n_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].eat_n_time = 0;
		i++;
	}
	return (philo);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;
	size_t				i;

	i = 0;
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	while (i < (nmemb * size))
	{
		res[i] = '\0';
		i++;
	}
	return ((void *)res);
}
