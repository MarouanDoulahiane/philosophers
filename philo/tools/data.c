/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 08:17:28 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/03 08:24:39 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	push_back(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	tmp = *philo;
	if (!tmp)
	{
		*philo = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_philo	*new_philo(int id, int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->nb_philo = ft_atoi(av[0]);
	philo->time_to_die = ft_atoi(av[1]);
	philo->time_to_eat = ft_atoi(av[2]);
	philo->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		philo->nb_eat = ft_atoi(av[4]);
	else
		philo->nb_eat = -1;
	philo->eat_count = 0;
	philo->start_time = 0;
	philo->last_meal = 0;
	philo->next = NULL;
	return (philo);
}

long	get_time(void)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(1);
}
