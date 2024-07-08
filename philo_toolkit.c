/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_toolkit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:54:47 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/08 14:48:31 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

int	isdigit(int c)
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


long ft_atoi(char *str)
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
