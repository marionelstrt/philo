/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 04:43:09 by mtarento          #+#    #+#             */
/*   Updated: 2025/03/06 23:47:02 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_monitoring(t_table *table)
{
	if (pthread_create(&table->monitor_thread,
			NULL, monitor_routine, table) != 0)
	{
		write(1, "failed creating monitor thread\n", 32);
		exit(1);
	}
}

void	ft_grave(t_table *table, int id)
{
	pthread_mutex_lock(&table->is_dead);
	table->dead = 1;
	pthread_mutex_unlock(&table->is_dead);
	print_status(&table->philos[id], DEAD);
}

int	check_philosopher_death(t_table *table)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		time_since_last_meal = get_time() - table->philos[i].last_meal;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		if (time_since_last_meal >= table->time_to_die)
		{
			ft_grave(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	are_you_done_yet(t_table *table)
{
	int	i;
	int	done_philo;

	i = 0;
	done_philo = 0;
	if (table->must_eat <= 0)
		return (0);
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals_eaten >= table->must_eat)
			done_philo++;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	if (done_philo == table->num_philos)
	{
		pthread_mutex_lock(&table->is_dead);
		table->dead = 1;
		pthread_mutex_unlock(&table->is_dead);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->is_dead);
		if (table->dead)
		{
			pthread_mutex_unlock(&table->is_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&table->is_dead);
		if (check_philosopher_death(table) || are_you_done_yet(table))
			return (NULL);
		ft_usleep(100);
	}
	return (NULL);
}
