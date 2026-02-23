/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:23:12 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/23 12:32:41 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_content(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i])
		return (0);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	validate_arg(char *arg, int min, int max)
{
	int	n;

	if (!check_content(arg))
		return (-1);
	n = ft_atoi(arg);
	if (n < min || (max != -1 && n > max))
		return (-1);
	return (n);
}

int	valid_args(char **argv, int argc)
{
	if (validate_arg(argv[1], 1, 200) == -1)
		return (printf("Invalid philosophers number\n"), 0);
	if (validate_arg(argv[2], 1, -1) == -1)
		return (printf("Invalid time to die\n"), 0);
	if (validate_arg(argv[3], 1, -1) == -1)
		return (printf("Invalid time to eat\n"), 0);
	if (validate_arg(argv[4], 1, -1) == -1)
		return (printf("Invalid time to sleep\n"), 0);
	if (argc == 6)
	{
		if (validate_arg(argv[5], 1, -1) == -1)
			return (printf("Meals to eat must be > 0"), 0);
	}
	return (1);
}
