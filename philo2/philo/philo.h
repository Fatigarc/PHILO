/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatigarc <fatigarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 08:51:30 by fatigarc          #+#    #+#             */
/*   Updated: 2026/02/21 11:31:05 by fatigarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_program
{
	int				dead_flag;
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			meal_target;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}					t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_program		*program;
}					t_philo;

//philo.c
void	check_all_ate(t_program *program);
void	*routine_loop(t_philo *philo);
void	*one_philo_case(t_philo *philo);

//parser.c
int		valid_args(char **argv, int argc);

//utils.c
void	destroy_all(t_program *program);
long	get_time(void);
int		ft_atoi(const char *str);
void	print_action(t_philo *philo, char *action);
int		allocate_memory(t_program *program, char **argv);

//philo_threads.c
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
void	thread_create(t_program *program);

//init.c
void	init_philos(t_program *program);
int		init_mutex(t_program *program);
void	init_settings(t_program *program, char **argv, int argc);

//actions.c
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif
