/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 04:27:14 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 05:10:18 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

bool	num_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		fprintf(stderr, "Usage: ./philo <number_of_philosophers> ");
		fprintf(stderr, "<time_to_die> <time_to_eat> <time_to_sleep> ");
		fprintf(stderr, "[optional] ");
		fprintf(stderr, "<number_of_times_each_philosopher_must_eat>\n");
		return (true);
	}
	return (false);
}

bool	syntax(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				fprintf(stderr, "Error!\n");
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	valid_args(int ac, char **av)
{
	if (num_arg(ac) || syntax(ac, av))
		exit(1);
}
