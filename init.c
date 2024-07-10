/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:04:04 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/10 18:37:32 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

int init_data(t_moniter *data, char **argv)
{
	data->rsvps = ft_atol(argv[1]);
	data->hemlock_time = ft_atol(argv[2]);
	data->dinner_bell = ft_atol(argv[3]);
	data->drunken_stupor = ft_atol(argv[4]);
	if (argv[5])
		data->feasts = ft_atol(argv[5]);
	else
		data->feasts = -1;
	data->symposium_start = kronosophize();
	ft_usleep(100);
	data->current_time = update_krono(data->symposium_start);
	return (0);
}

int init_moniter(t_moniter *alcibiades, char **argv)
{
	alcibiades->plato = NULL;
	alcibiades->full_philos = 0;
	alcibiades->rsvps = ft_atol(argv[1]);
	alcibiades->hemlock_time = ft_atol(argv[2]);
	alcibiades->dinner_bell = ft_atol(argv[3]);
	alcibiades->drunken_stupor = ft_atol(argv[4]);
	alcibiades->plato = malloc(sizeof(t_plato) * alcibiades->rsvps);
	if (alcibiades->plato == NULL)
		return (EXIT_MALLOC_FAIL);
	alcibiades->symposium_start = kronosophize();
	alcibiades->current_time = update_krono(alcibiades->symposium_start);
	if (pthread_mutex_init(&alcibiades->lock_print, NULL) != 0)
		return(EXIT_MUTEX_INIT_ERROR);
	return (0);
}

int init_plato(t_plato *plato, t_moniter *data)
{
	int i;

	i = 0;

	while (i < data->rsvps)
	{
		memset(&plato[i], 0, sizeof(t_plato));
		if (init_mutexes(plato, data->rsvps) == 1)
		{
			destroy_fork_mutexes(plato);
			printf("Error inititalizing data mutexes\n");
			return (1);
		}
		plato[i].id = i + 1;
		plato[i].alcibiades = data;
		if (data->rsvps == 1)
			plato[i].l_fork  = NULL;
		if (i < data->rsvps)	
			plato[i].l_fork = plato[i + 1].r_fork;
		else if (i == data->rsvps)
			plato[i].l_fork = plato[0].r_fork;
		if (pthread_mutex_init(&plato[i].meal_lock, NULL) != 0)
		{
			destroy_fork_mutexes(plato);
			printf("Error initializing meal_lock mutex \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int check_status(t_plato *plato, t_moniter *data)
{
	int i;

	i = 0;
	
	while (i <= data->rsvps)
	{
		if (plato->id == i)
		{
			if (plato->hemlock == true)
			{
				printf("Philo %d has died at %zu\n", plato->id, data->current_time);
				return (1);
			}
			if (data->feasts > 0)
			{	if (plato->meals_consumed > data->feasts)
				{
					printf("Philo %d is full\n", plato->id); 
					return (2);
				}
			}
		}
	i++;
	}
	return (0);
}

int symp_routine(t_plato *plato, t_moniter *data)
{
	if (check_status(plato, data) == 1)
		return (1);
//	if (plato ->id % 2 == 1)

//		pthread_mutex_lock(plato->
				//check flags/death flags
				//lock down the forks
				//usleep for argv amount of time to eat
				//write time of day
				//write "Philo 1 eats"
				//unlock forks
				//set HUNGER timer
				//usleep for argv amount to sleep
				//write time of day
				//write philo 1 sleeps
	return (0);
}

//int init_threads(t_plato *plato, t_moniter *data)
//{
//	return (0);	
//}

