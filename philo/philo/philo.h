/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:03:59 by mtarento          #+#    #+#             */
/*   Updated: 2025/03/05 18:13:45 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef enum e_action
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_action;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long int		last_meal;
	pthread_t		thread;
	t_table			*table;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long int		start_time;
	int				dead;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	can_print;
	pthread_mutex_t	is_dead;
	int				finished_philos;
	pthread_mutex_t	finished_mutex;
	t_philo			*philos;
}	t_table;

// Utils
int		ft_usleep(size_t milliseconds);
int		is_digit(char c);
void	start_monitoring(t_table *table);
int		only_digit(char *av[]);
int		ft_atoi(char *str);
long	get_time(void);
int		check_args(int ac, char *av[]);
void	destroy_mutex(t_table *table);
void	*monitor_routine(void *arg);
void	release_forks(t_philo *philo);
void	take_forks(t_philo *philo);
void	print_status(t_philo *philo, t_action action);
void	ft_grave(t_table *table, int id);
int		check_philosopher_death(t_table *table);
int		are_you_done_yet(t_table *table);
void	*philosopher_routine(void *arg);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

#endif
