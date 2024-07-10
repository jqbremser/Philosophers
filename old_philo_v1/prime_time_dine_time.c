/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:57:57 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/10 18:37:35 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

int check_arg(char *argv)
{
	if (ft_atol(argv) < 0)
	{
		printf("Values must be non-zero positive integers\n");
		return (1);
	}
	if (isdigit(ft_atol(argv)) == 1)
	{
		printf("Reality is subjective!\n");
		return (1);
	}
	return (0);
}

int check_params(int argc, char **argv)
{
	int i;

	i = 1;
	if (ft_atol(argv[1]) <= 0)
	{
		printf("Hire more sophists\n");
		return (1);
	}
	while (i < argc)
	{
		if (check_arg(argv[i]) == 1)
			return (1);
		i++;
	}
	if (ft_atol(argv[i - 1]) == 0)
	{
		printf("How does one eat zero meals?\n");
		return(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;
	t_plato *plato;
	
	if (argc == 5 || argc == 6)
	{	
		if (check_params(argc, argv) == 1)
			return (1);
		else if (init_data(&data, argv) == 1)
			return (clean_data(&data));
		plato = malloc(sizeof(t_plato) * data.rsvps);
		if (!plato)
			return (1);
		if (init_plato(plato, &data) == 1)
			return (destroy_fork_mutexes(plato));
//		if (init_threads(plato, &data) == 1)
//		{
//			cleanup(plato, &data);
//			return (1);
//		}
//		cleanup(plato, &data);
		if (symp_routine(plato, &data) > 0)
			return (clean_data(&data));
		print_structs(data, plato);
	}
	else
		printf("needs more Args\n");
	return (0);
}

