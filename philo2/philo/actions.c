/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:22:48 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/23 12:18:48 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock); //lo borré sin querer en algún punto.
	if (philo->id % 2 == 0)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	else
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
}

//luego moverlo y verificarlo.

int	smart_pause(t_philo *phi, long duration)
{
	long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&phi->program->dead_lock);
		if(phi->program->dead_flag == 1)
		{
			pthread_mutex_unlock(&phi->program->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&phi->program->dead_lock);
		if (get_time() - start >= duration)
			break ;
		usleep(100);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	lock_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->eating = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	if (smart_pause(philo, philo->program->time_to_eat))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eating = 0;
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	print_action(philo, "is sleeping");
	if (smart_pause(philo, philo->program->time_to_sleep))
		return ;
	//usleep(philo->program->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	print_action(philo, "is thinking");
	if (smart_pause(philo, 1))
		return ;
}
