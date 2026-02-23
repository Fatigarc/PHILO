/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 08:50:47 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/23 12:17:16 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_ate(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->philos[i].meal_mutex);
		if (program->philos[i].meals_eaten < program->meal_target)
		{
			pthread_mutex_unlock(&program->philos[i].meal_mutex);
			return ;
		}
		pthread_mutex_unlock(&program->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&program->dead_lock);
	program->dead_flag = 1;
	pthread_mutex_unlock(&program->dead_lock);
}

void	*routine_loop(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->program->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->program->dead_lock);
		if (philo->program->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->program->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->program->dead_lock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "A fork has been taken");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->program->time_to_die * 1000);
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->program->dead_flag = 1;
	pthread_mutex_unlock(&philo->program->dead_lock);
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%ld %d died\n", get_time() - philo->program->start_time, philo->id);
	pthread_mutex_unlock(&philo->program->write_lock);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), 1);
	if (valid_args(argv, argc) == 0)
		return (1);
	init_settings(&program, argv, argc);
	if (!allocate_memory(&program, argv))
		return (1);
	if (!init_mutex(&program))
		return (destroy_all(&program), 4);
	init_philos(&program);
	thread_create(&program);
	destroy_all(&program);
	return (0);
}
