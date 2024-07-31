/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_toolkit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:54:47 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 14:39:03 by jbremser         ###   ########.fr       */
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
		if (ft_atol(argv[i]) <= 0)
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

void print_structs(t_philo *philo)
{
	printf("\nPHILO ID:%d\n", philo->id);
	printf("rsvps:%d\n", philo->overseer->rsvps);
	printf("hemlock_time:%zu\n", philo->hemlock_time);
	printf("Dinner_bell:%ld\n", philo->dinner_bell);
	printf("Drunken_stupor:%d\n", philo->drunken_stupor);
	printf("Feasts:%d\n", philo->feasts);
	printf("Start of Symposium:%zu\n", philo->overseer->symposium_start);
	printf("Current time: %zu\n", philo->current_time);
	printf("Meals consumed: %d\n\n", philo->meals_consumed);
//	int i = 0;
//	while (i < moniter.rsvps)
//	{
//		printf("Philo#%d:%d\n", i + 1, philo[i].id);
//		printf("Philo#%d meals consumed:%d\n", philo[i].id, philo[i].meals_consumed);
//		i++;
//	}
}
