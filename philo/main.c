/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:18:02 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/03 18:14:53 by mdoulahi         ###   ########.fr       */
/*                                                                             */
/* ************************************************************************** */

#include "includes/philo.h"

void	initialize_mutex(t_philo **philo)
{
	int				i;
	pthread_mutex_t	*data;
	pthread_mutex_t	*print;
	t_philo			*tmp;

	data = malloc(sizeof(pthread_mutex_t));
	if (!data)
		return ;
	print = malloc(sizeof(pthread_mutex_t));
	if (!print)
		return ;
	tmp = *philo;
	i = 0;
	pthread_mutex_init(data, NULL);
	pthread_mutex_init(print, NULL);
	while (i < tmp->nb_philo)
	{
		tmp->data = data;
		tmp->print = print;
		pthread_mutex_init(&tmp->forks, NULL);
		tmp = tmp->next;
		i++;
	}
}

void	addition_routine(t_philo *philo)
{
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->next->forks);
	pthread_mutex_unlock(&philo->forks);
	pthread_mutex_lock(philo->print);
	printf("%ld %d is sleeping\n", get_time() - philo->start_time, \
			philo->id);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->print);
	printf("%ld %d is thinking\n", get_time() - philo->start_time, \
			philo->id);
	pthread_mutex_unlock(philo->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		pthread_mutex_lock(&philo->forks);
		pthread_mutex_lock(&philo->next->forks);
		pthread_mutex_lock(philo->print);
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time, \
				philo->id);
		pthread_mutex_unlock(philo->print);
		pthread_mutex_lock(philo->print);
		printf("%ld %d is eating\n", get_time() - philo->start_time, \
				philo->id);
		pthread_mutex_unlock(philo->print);
		pthread_mutex_lock(philo->data);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->data);
		pthread_mutex_lock(philo->data);
		philo->eat_count++;
		pthread_mutex_unlock(philo->data);
		addition_routine(philo);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (!check_valid_args(ac - 1, av + 1))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (ft_atoi(av[1]) == 0)
	{
		printf("Error: Number of philosophers must be greater than 0\n");
		return (1);
	}
	initialize_philo(&philo, ac - 1, av + 1);
	free_philo(philo);
	return (0);
}
