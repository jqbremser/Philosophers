/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_toolkit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:54:47 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/24 17:16:40 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

size_t kronosophize(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL) == -1)
		printf("Lauren's function is not working\n");
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(size_t mili)
{
	size_t start;

	start = kronosophize();
	while ((kronosophize() - start) < mili)
		usleep(500);
}

size_t update_krono(size_t start_time)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}

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
