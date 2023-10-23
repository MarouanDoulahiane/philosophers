/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cypher <cypher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:47:43 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/10/23 16:30:05 by cypher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	main(int ac, char **av)
{
	valid_args(ac, av);
	monitor(ac, av);
	// data = data_init(ac, av);
	// philo = philo_init(data);
	// fork = ft_calloc(data->n_philosophers, sizeof(int));
	// int i = 0;
	// while (i < data->n_philosophers)
	// {
	// 	printf("==== Philo (id:%d) ====\n", philo[i].id);
	// 	printf("\teat %d time\n", philo[i].eat_n_time);
	// 	printf("\tfork state %d\n", fork[i]);
	// 	i++;
	// }

	return (0);
}
