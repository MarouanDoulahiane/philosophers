/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:19:05 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/03 08:38:23 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->data);
	if (get_time() - philo->last_meal > philo->time_to_die)
	{
		usleep(300);
		pthread_mutex_lock(philo->print);
		printf("%ld %d died\n", get_time() - philo->start_time, philo->id);
		return (1);
	}
	pthread_mutex_unlock(philo->data);
	return (0);
}

int	philo_eat_enough(t_philo *philo)
{
	int	i;
	int	count_eat_enough;

	i = 0;
	count_eat_enough = 0;
	if (philo->nb_eat == -1)
		return (0);
	while (i < philo->nb_philo)
	{
		pthread_mutex_lock(philo->data);
		if (philo->eat_count >= philo->nb_eat)
			count_eat_enough++;
		pthread_mutex_unlock(philo->data);
		i++;
		philo = philo->next;
	}
	if (count_eat_enough == philo->nb_philo)
	{
		pthread_mutex_lock(philo->print);
		printf("All philosophers have eaten enough\n");
		return (1);
	}
	return (0);
}

int	start_simulation(t_philo **philo, pthread_t *thread, long start_time)
{
	int		i;
	t_philo	*tmp;

	i = -1;
	tmp = *philo;
	while (++i < tmp->nb_philo)
	{
		tmp->start_time = start_time;
		if (pthread_create(&thread[i], NULL, &routine, tmp))
			return (printf("Error: Can't create thread\n"));
		tmp = tmp->next;
		usleep(300);
	}
	while (true)
	{
		if (philo_die(tmp) || philo_eat_enough(tmp))
			return (0);
	}
	i = 0;
	while (i < tmp->nb_philo)
	{
		if (pthread_join(thread[i++], NULL))
			return (printf("Error: Can't join thread\n"));
	}
	return (0);
}

void	initialize_philo(t_philo **philo, int ac, char **av)
{
	int			id;
	int			nb_philo;
	pthread_t	*thread;
	t_philo		*tmp;

	id = 1;
	nb_philo = ft_atoi(av[0]);
	while (id <= nb_philo)
	{
		push_back(philo, new_philo(id, ac, av));
		id++;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *philo;
	thread = malloc(sizeof(pthread_t) * nb_philo);
	if (!thread)
		return ;
	initialize_mutex(philo);
	start_simulation(philo, thread, get_time());
	free(thread);
}

void	free_philo(t_philo *philo)
{
	int		i;
	int		nb_philo;
	t_philo	*tmp;

	i = 0;
	nb_philo = philo->nb_philo;
	pthread_mutex_destroy(philo->data);
	pthread_mutex_destroy(philo->print);
	free(philo->data);
	free(philo->print);
	while (i < nb_philo)
	{
		tmp = philo->next;
		pthread_mutex_destroy(&philo->forks);
		free(philo);
		philo = tmp;
		i++;
	}
}
