/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_toolkit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:54:47 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/24 18:44:28 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static int	isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long ft_atol(char *str)
{
	long num;

	if (ft_strlen(str) > 10)
		return (-1);
	num = 0;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		num = (num * 10 + (*str - '0'));
		str++;
	}
	if (*str || num > INT_MAX)
		return(-1);
	return (num);
}

int check_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_atol(argv[i]) < 0)
			return (EXIT_INVALID_ARGS);
		if (isdigit(ft_atol(argv[i])) == 1)
			return (EXIT_INVALID_ARGS);
		if (argv[5])
		{
			if (ft_atol(argv[5]) == 0)
				return (EXIT_INVALID_ARGS);
		}
		i++;
	}
	return (0);
}

void print_structs(t_plato *plato)
{
	printf("\nPHILO ID:%d\n", plato->id);
	printf("rsvps:%d\n", plato->alcibiades->rsvps);
	printf("Hemlock_time:%zu\n", plato->hemlock_time);
	printf("Dinner_bell:%d\n", plato->dinner_bell);
	printf("Drunken_stupor:%d\n", plato->drunken_stupor);
	printf("Feasts:%d\n", plato->feasts);
	printf("Start of Symposium:%zu\n", plato->symposium_start);
	printf("Current time: %zu\n", plato->current_time);
	printf("Meals consumed: %d\n\n", plato->meals_consumed);
//	int i = 0;
//	while (i < moniter.rsvps)
//	{
//		printf("Philo#%d:%d\n", i + 1, plato[i].id);
//		printf("Philo#%d meals consumed:%d\n", plato[i].id, plato[i].meals_consumed);
//		i++;
//	}
}
