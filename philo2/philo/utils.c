/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:23:42 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/21 10:17:31 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_program *program)
{
	int	i;

	i = 0;
	if (program->forks != NULL)
	{
		while (i < program->num_of_philos)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	if (program->philos != NULL)
		free(program->philos);
	if (program->forks != NULL)
		free(program->forks);
	program->philos = NULL;
	program->forks = NULL;
}

long	get_time(void)
{
	struct timeval	tv;
	long			second_to_ms;
	long			microsec_to_ms;

	gettimeofday(&tv, NULL);
	second_to_ms = tv.tv_sec * 1000;
	microsec_to_ms = tv.tv_usec / 1000;
	return (second_to_ms + microsec_to_ms);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	pthread_mutex_lock(&philo->program->write_lock);
	timestamp = get_time() - philo->program->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}

int	allocate_memory(t_program *program, char **argv)
{
	int				n;

	n = ft_atoi(argv[1]);
	program->num_of_philos = n;
	program->philos = malloc(sizeof(t_philo) * n);
	if (!program->philos)
		return (0);
	memset(program->philos, 0, sizeof(t_philo) * n);
	program->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!program->forks)
	{
		free(program->philos);
		program->philos = NULL;
		return (0);
	}
	return (1);
}
