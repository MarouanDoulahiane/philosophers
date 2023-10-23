/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cypher <cypher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:57:19 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 23:20:22 by cypher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	who_eat_first(t_holder	*holder)
{
	int	size = holder->data->n_philosophers;
	int min = INT_MAX;
	int i = 0;
	while (i < size)
	{
		if (min > holder->philo[i].eat_n_time)
			min = holder->philo[i].eat_n_time;
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (min == holder->philo[i].eat_n_time)
			holder->philo[i].able_to_eat = true;
		else
			holder->philo[i].able_to_eat = false;
		i++;
	}
}
void	*func(void *arg)
{
	t_holder	*holder = (t_holder *)arg; 
	int	i = holder->philo[holder->i].id;
	int	size = holder->data->n_philosophers;
	while (1)
	{
		if (holder->philo[i - 1].able_to_eat)
		{
			printf("gg\n");
			pthread_mutex_lock(&(holder->general_mutex));			
			if (i - 1 != i % size && holder->fork[i - 1] == 0 && holder->fork[i % size] == 0)
			{	
				holder->fork[i - 1] = 1;
				holder->fork[i % size] = 1;
				// printf("deadlock [%d:%d ; %d:%d]\t%d\n", i - 1, holder->fork[i - 1], i % size, holder->fork[i % size], i);
				pthread_mutex_unlock(&(holder->general_mutex));
				pthread_mutex_lock(&(holder->fork_mutex[i - 1]));
				pthread_mutex_lock(&(holder->fork_mutex[i % size]));
				printf("(id:%d): Hello!\n", i);
				holder->fork[i - 1] = 0;
				holder->fork[i % size] =0;
				holder->philo[i - 1].eat_n_time++;
				who_eat_first(holder);
				sleep(1);
				pthread_mutex_unlock(&(holder->fork_mutex[i % size]));
				pthread_mutex_unlock(&(holder->fork_mutex[i - 1]));
			}
			else
				pthread_mutex_unlock(&(holder->general_mutex));
		}
	}
	return (NULL);
}

void	monitor(int ac, char **av)
{
	pthread_t	*th;
	int				i;
	int				j;
	t_holder	**holder;
	int			size;

	size = ft_atoi(av[1]);
	holder = (t_holder **)malloc(sizeof(t_holder *) * size);
	if (!holder)
		return ;

	

	th = (pthread_t *)malloc(sizeof(pthread_t) * size);
	if (!th)
		return ;
	i = 0;
	while (i < size)
	{
		holder[i] = (t_holder *)malloc(sizeof(t_holder));
		if (i == 0)
		{	
			holder[i]->data = data_init(ac, av);
			holder[i]->philo = philo_init(holder[i]->data);
			holder[i]->fork = ft_calloc(holder[i]->data->n_philosophers, sizeof(int));
			pthread_mutex_init(&(holder[i]->general_mutex), NULL);
			j = 0;
			holder[i]->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
			while (j < size)
			{
				pthread_mutex_init(&(holder[i]->fork_mutex[j]), NULL);
				j++;
			}
			who_eat_first(holder[0]);
		}
		else
		{
			holder[i]->general_mutex = holder[0]->general_mutex;
			holder[i]->fork_mutex = holder[0]->fork_mutex;
			holder[i]->data = holder[0]->data;
			holder[i]->philo = holder[0]->philo;
			holder[i]->fork = holder[0]->fork;
		}
		holder[i]->i = i;
		if (pthread_create(&th[i], NULL, &func, holder[i]))
		{
			printf("failed to create\n");
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pthread_join(th[i], NULL))
		{
			printf("failed to join\n");
		}
		i++;
	}
	free(th);
	free(holder[0]->data);
	free(holder[0]->philo);
	free(holder[0]->fork);
	pthread_mutex_destroy(&(holder[0]->general_mutex));
	j = 0;

	while (j < size)
	{
		pthread_mutex_destroy(&(holder[0]->fork_mutex[j]));
		j++;
	}
	free(holder[0]->fork_mutex);
	i = 0;
	while (i < size)
	{
		free(holder[i]);
		i++;
	}
	free(holder);
}

