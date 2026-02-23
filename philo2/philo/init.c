/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:22:59 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/21 11:48:42 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].program = program;
		program->philos[i].meals_eaten = 0;
		program->philos[i].eating = 0;
		program->philos[i].last_meal = program->start_time;
		pthread_mutex_init(&program->philos[i].meal_mutex, NULL);
		program->philos[i].r_fork
			= &program->forks[(i + 1) % program->num_of_philos];
		program->philos[i].l_fork = &program->forks[i];
		i++;
	}
}

int	init_mutex(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&program->forks[i]);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (0);
	return (1);
}

void	init_settings(t_program *program, char **argv, int argc)
{
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->meal_target = ft_atoi(argv[5]);
	else
		program->meal_target = -1;
	program->start_time = get_time();
	program->dead_flag = 0;
}
