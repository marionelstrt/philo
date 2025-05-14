/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:44:06 by mtarento          #+#    #+#             */
/*   Updated: 2025/03/07 20:31:59 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int ac, char *av[])
{
	table->num_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	else
		table->must_eat = -1;
	table->start_time = get_time();
	table->dead = 0;
}

void	init_mutex(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philos[i].meal_mutex, NULL);
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork
			= &table->forks[(i + 1) % table->num_philos];
		i++;
	}
	pthread_mutex_init(&table->can_print, NULL);
	pthread_mutex_init(&table->finished_mutex, NULL);
	pthread_mutex_init(&table->is_dead, NULL);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->can_print);
	pthread_mutex_destroy(&table->is_dead);
	pthread_mutex_destroy(&table->finished_mutex);
	free(table->forks);
	free(table->philos);
	return ;
}

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philosopher_routine, &table->philos[i]) != 0)
		{
			write(1, "failed creating thread\n", 23);
			return ;
		}
		usleep(100);
		i++;
	}
	start_monitoring(table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}

int	main(int ac, char *av[])
{
	long	n;
	t_table	*table;

	if (check_args(ac, av))
		return (1);
	if (ft_atoi(av[1]) == 1)
	{
		printf("0 Philosopher 0 has taken a fork\n");
		n = get_time();
		usleep(ft_atoi(av[2]) * 1000);
		printf("%ld Philosopher 0 has died \n", get_time() - n);
		return (0);
	}
	table = malloc(sizeof(t_table));
	init_table(table, ac, av);
	init_mutex(table);
	create_threads(table);
	destroy_mutex(table);
	free(table);
	return (0);
}
