/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarento <mtarento@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:06:36 by mtarento          #+#    #+#             */
/*   Updated: 2025/03/07 18:52:51 by mtarento         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	only_digit(char *av[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char *av[])
{
	if (ac != 5 && ac != 6)
	{
		write(1, "wrong number of args\n", 21);
		return (1);
	}
	if (!only_digit(av))
	{
		printf("arguments must be only digits and positive\n");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
	{
		printf("args at zero or inferior\n");
		return (1);
	}
	return (0);
}
