/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_toolkit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:54:47 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/18 15:23:19 by jbremser         ###   ########.fr       */
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


static int check_ov(int neg)
{
	if (neg == 1)
			return ((int) FT_LONG_MAX);
	return ((int)-FT_LONG_MAX - 1L);
}


int anti_plato(char *str)
{
	int neg;
	long num;
	long temp;

	if (ft_strlen(str) > 10)
		return (-1);
	num = 0;
	neg = 1;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -neg;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		temp = num;
		num = (num * 10 + (*str - '0'));
		if (num < 0 || temp > num)
			return (check_ov(neg));
		str++;
	}
	return (neg * num);
}
