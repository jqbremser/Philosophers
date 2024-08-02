/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:51:15 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/01 16:54:52 by jbremser         ###   ########.fr       */
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
    while(argv[i])
    {
        if ((ft_atol(argv[i]) <= 0) || (isdigit(ft_atol(argv[i])) == 1))
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

