/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:47:43 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 15:49:32 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	int		*fork;

	valid_args(ac, av);
	data = data_init(ac, av);
	philo = philo_init(data);
	fork = ft_calloc(data->n_philosophers, sizeof(int));
	int i = 0;
	while (i < data->n_philosophers)
	{
		printf("==== Philo (id:%d) ====\n", philo[i].id);
		printf("\teat %d time\n", philo[i].eat_n_time);
		printf("\tfork state %d\n", fork[i]);
		i++;
	}
	free(data);
	free(philo);
	free(fork);
	return (0);
}
