/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:57:57 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/24 17:16:43 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

void print_structs(t_data data, t_plato *plato)
{
	printf("rsvps:%d\n", data.rsvps);
	printf("Hemlock_time:%d\n", data.hemlock_time);
	printf("Dinner_bell:%d\n", data.dinner_bell);
	printf("Drunken_stupor:%d\n", data.drunken_stupor);
	printf("Feasts:%d\n", data.feasts);
	printf("Start of Symposium:%zu\n", data.symposium_start);
	printf("Current time: %zu\n", data.current_time);
	int i = 0;
	while (i < data.rsvps)
	{
		printf("Philo#%d:%d\n", i + 1, plato[i].id);
		printf("Philo#%d meals consumed:%d\n", plato[i].id, plato[i].meals_consumed);
		i++;
	}
}

int check_arg(char *argv)
{
	int i;
	i = 0;

	if (anti_plato(argv) < 0)
	{
		printf("Values must be positive\n");
		return (0);
	}
		
	while (argv[i])
	{
		if (isdigit(argv[i]) == 0)
		{
			printf("Reality is subjective!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

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
		if (check_arg(argv[i]) == 0)
			return (0);		
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data data;
	t_plato *plato;
	
	if (argc == 5 || argc == 6)
	{	
		if (check_params(argc, argv) == 0)
			return (0);
		else if (init_data(&data, argv) == 0)
			return (0);
		plato = malloc(sizeof(t_plato) * data.rsvps);
		if (!plato)
			return (0);
		if (init_plato(plato, data) == 0)
			return (0);
		print_structs(data, plato);
	}
	else
		printf("needs more Args\n");
	return (1);
}

