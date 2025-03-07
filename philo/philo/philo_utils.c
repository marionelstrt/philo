/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:59:30 by mtarento          #+#    #+#             */
/*   Updated: 2025/03/06 23:36:20 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	num;
	int	i;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] <= ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

void	print_status(t_philo *philo, t_action action)
{
	long	timestamp;	

	pthread_mutex_lock(&philo->table->is_dead);
	if (philo->table->dead && action != DEAD)
	{
		pthread_mutex_unlock(&philo->table->is_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->is_dead);
	pthread_mutex_lock(&philo->table->can_print);
	timestamp = get_time() - philo->table->start_time;
	if (action == TAKEN_FORK)
		printf("%ld Philosopher %d has taken a fork\n", timestamp, philo->id);
	else if (action == EATING)
		printf("%ld Philosopher %d is eating\n", timestamp, philo->id);
	else if (action == SLEEPING)
		printf("%ld Philosopher %d is sleeping\n", timestamp, philo->id);
	else if (action == THINKING)
		printf("%ld Philosopher %d is thinking\n", timestamp, philo->id);
	else if (action == DEAD)
		printf("%ld Philosopher %d has died \n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->can_print);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}
