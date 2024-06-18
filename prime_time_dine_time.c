/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:57:57 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/18 15:30:59 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

int check_params(int argc, char **argv)
{
	int i;

	i = 1;
	if (anti_plato(argv[1]) <= 0)
	{
		printf("Hire more sophists\n");
		return (0);
	}
	while (i < argc)
	{
		if (isdigit(anti_plato(argv[i])) == 0)
		{
			printf("Invalid Input\n");
			return (0);
		}
		else if (anti_plato(argv[i]) < 0)
		{
			printf("Values must be positive\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data data;
	
	if (argc == 5 || argc == 6)
	{	
		if (check_params(argc, argv) == 0)
			return (0);
		if (init_data(&data, argv) != 0)
			return (1);
		printf("rsvps:%d\n", data.rsvps);
		printf("Hemlock_time:%d\n", data.hemlock_time);
		printf("Dinner_bell:%d\n", data.dinner_bell);
		printf("Drunken_stupor:%d\n", data.drunken_stupor);
		printf("Feasts:%d\n", data.feasts);
	}
	return (1);
}
