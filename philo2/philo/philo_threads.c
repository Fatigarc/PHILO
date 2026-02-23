/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:23:27 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/23 11:56:52 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_death(t_program *program, int id)
{
	pthread_mutex_lock(&program->write_lock);
	printf("%ld %d died\n", get_time() - program->start_time, id);
	pthread_mutex_unlock(&program->write_lock);
}

static void	monitor_loop2(t_program *program)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->philos[i].meal_mutex);
		time_since_last_meal = get_time() - program->philos[i].last_meal;
		pthread_mutex_unlock(&program->philos[i].meal_mutex);
		pthread_mutex_lock(&program->dead_lock);
		if (!program->dead_flag && time_since_last_meal > program->time_to_die)
		{
			program->dead_flag = 1;
			print_death(program, program->philos[i].id);
			pthread_mutex_unlock(&program->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&program->dead_lock);
		i++;
	}
	if (program->meal_target > 0)
		check_all_ate(program);
	usleep(100);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *) arg;
	while (1)
	{
		monitor_loop2(program);
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag)
		{
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&program->dead_lock);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->program->num_of_philos == 1)
		return (one_philo_case(philo));
	else
		return (routine_loop(philo));
}

void	thread_create(t_program *program)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philo_routine, &program->philos[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, program) != 0)
		return ;
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
