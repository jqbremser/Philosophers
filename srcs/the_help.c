/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:51:15 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/03 17:27:53 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	long	num;

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
		return (-1);
	return (num);
}

static int	jaakko_jeekkeri(char *argv)
{
	long	num;
	long	temp;

	num = ft_atol(argv);
	temp = 0;
	if (num < 0)
		return (1);
	if (num == 0)
		return (0);
	while (num > 0)
	{
		temp = num % 10;
		if (temp < 0 || temp > 9)
			return (1);
		num /= 10;
	}
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (jaakko_jeekkeri(argv[i]))
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
