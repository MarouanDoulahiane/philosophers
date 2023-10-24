/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cypher <cypher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:57:19 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/25 00:25:59 by cypher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	free_memory(t_holder ***ref_holder)
{
	t_holder **holder;
	int			size;
	int			j;

	holder = *ref_holder;
	size = holder[0]->data->n_philosophers;
	free(holder[0]->th);
	free(holder[0]->data);
	free(holder[0]->philo);
	free(holder[0]->fork);
	pthread_mutex_destroy(&(holder[0]->general_mutex));
	pthread_mutex_destroy(&(holder[0]->message));
	j = 0;

	while (j < size)
	{
		pthread_mutex_destroy(&(holder[0]->fork_mutex[j]));
		j++;
	}
	free(holder[0]->fork_mutex);
	j = 0;
	while (j < size)
	{
		free(holder[j]);
		j++;
	}
	free(holder);
}

long	actual_time(void)
{
	long			time;
	struct timeval	curr;

	if (gettimeofday(&curr, NULL) == -1)
	{
		printf("Error: gettimeofday return -1\n");
		exit(-1);
	}
	time = (curr.tv_sec * 1000) + (curr.tv_usec / 1000);
	return (time);
}

void	*func(void *arg)
{
	t_holder	*holder = (t_holder *)arg;
	int	i = holder->philo[holder->i].id;
	int	size = holder->data->n_philosophers;
	long	start_time = actual_time(); 
	long	time_wait_eat = actual_time();
	bool isLocked = false;
	long take_fork;
	long eat;
	long sleep;

	while (holder->data->n_time_to_eat == -1 || holder->philo[i - 1].eat_n_time < holder->data->n_time_to_eat)
	{

		if (isLocked)
		{
			pthread_mutex_lock(&(holder->message));
			printf("%ldms %d  has taken a fork\n", take_fork, i);
			printf("%ldms %d  has taken a fork\n", take_fork, i);
			printf("%ldms %d  is eating\n", eat, i);
			printf("%ldms %d  is sleeping\n", sleep, i);
			printf("%ldms %d  is thinking\n", actual_time() - start_time, i);
			if (time_wait_eat + holder->data->time_to_die <= actual_time())
			{
				printf("%ldms %d dead\n", actual_time() - start_time, i);
				return (NULL);
			}
			isLocked = false;
			pthread_mutex_unlock(&(holder->message));
		}
	
		pthread_mutex_lock(&(holder->general_mutex));			
		if (i - 1 != i % size && holder->fork[i - 1] == 0 && holder->fork[i % size] == 0)
		{	
			holder->fork[i - 1] = 1;
			holder->fork[i % size] = 1;
			pthread_mutex_unlock(&(holder->general_mutex));
			pthread_mutex_lock(&(holder->fork_mutex[i - 1]));
			pthread_mutex_lock(&(holder->fork_mutex[i % size]));
			isLocked = true;
			holder->fork[i - 1] = 0;
			holder->fork[i % size] =0;
			holder->philo[i - 1].eat_n_time++;
			// take forks
			take_fork = actual_time() - start_time;
			// eating
			eat = actual_time() - start_time;
			usleep(holder->data->time_to_eat * 1000);
			time_wait_eat = actual_time();
			pthread_mutex_unlock(&(holder->fork_mutex[i % size]));
			pthread_mutex_unlock(&(holder->fork_mutex[i - 1]));
			// sleeping
			sleep = actual_time() - start_time;
			usleep(holder->data->time_to_sleep * 1000);
			// here start thinking
		}
		else
			pthread_mutex_unlock(&(holder->general_mutex));
	}
	// free_memory(&holder);
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
			holder[i]->th = th;
			holder[i]->data = data_init(ac, av);
			holder[i]->philo = philo_init(holder[i]->data);
			holder[i]->fork = ft_calloc(holder[i]->data->n_philosophers, sizeof(int));
			pthread_mutex_init(&(holder[i]->general_mutex), NULL);
			pthread_mutex_init(&(holder[i]->message), NULL);
			j = 0;
			holder[i]->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
			while (j < size)
			{
				pthread_mutex_init(&(holder[i]->fork_mutex[j]), NULL);
				j++;
			}
			holder[i]->holder_tofree = holder;
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
	free_memory(&holder);
}
