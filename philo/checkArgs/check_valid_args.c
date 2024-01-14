/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:22:02 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/02 22:27:28 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	check_is_valid_positive_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < (int)n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// 2147483647

bool	check_is_positive_and_non_bigger_than_int_max(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i + j])
	{
		if (!ft_isdigit(str[i + j]))
			return (false);
		j++;
	}
	if (j > 10)
		return (false);
	if (j == 10 && ft_strncmp(str + i, "2147483647", 10) > 0)
		return (false);
	return (true);
}

bool	check_valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!check_is_valid_positive_int(av[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < ac)
	{
		if (!check_is_positive_and_non_bigger_than_int_max(av[i]))
			return (false);
		i++;
	}
	return (true);
}
