/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:34:03 by mtarento          #+#    #+#             */
/*   Updated: 2025/03/07 20:32:51 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->table->num_philos > 4)
			ft_usleep(100);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORK);
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	ft_usleep(philo->table->time_to_sleep);
	print_status(philo, THINKING);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->table->time_to_eat);
	release_forks(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->table->is_dead);
		if (philo->table->dead)
		{
			pthread_mutex_unlock(&philo->table->is_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->is_dead);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
