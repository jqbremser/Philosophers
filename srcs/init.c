/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:04:04 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/25 17:41:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void fill_plato(t_plato *plato, char **argv, t_moniter *alcibiades)
{
//		memset(plato, 0, sizeof(t_plato));
		plato->alcibiades = alcibiades;
		plato->hemlock_taken = &alcibiades->hemlock_taken;
		plato->hemlock_time = ft_atol(argv[2]);
		plato->dinner_bell = ft_atol(argv[3]);
		plato->drunken_stupor = ft_atol(argv[4]);
		if (argv[5])
			plato->feasts = ft_atol(argv[5]);
		else if (!argv[5])
			plato->feasts = -1;
		plato->current_time = update_krono(plato->symposium_start);
}

int init_moniter(t_moniter *alcibiades, char **argv)
{
	alcibiades->plato = NULL;
	alcibiades->full_philos = 0;
	alcibiades->rsvps = ft_atol(argv[1]);
	alcibiades->hemlock_taken = false;
	alcibiades->plato = malloc(sizeof(t_plato) * alcibiades->rsvps);
	if (alcibiades->plato == NULL)
		return (EXIT_MALLOC_FAIL);
	if (pthread_mutex_init(&alcibiades->hemlock, NULL) != 0)
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&alcibiades->print_lock, NULL) != 0)
		return (EXIT_MUTEX_INIT_ERROR);
	return (0);
}

int init_plato(t_moniter *alcibiades, char **argv)
{
	int			i;
	size_t		time;
//	pthread_t	grim;

	i = 0;
	time = kronosophize();
//	printf("start_time: %zu\n", time);
//	time = update_krono(time);
//	printf("updated_time: %zu\n", time);
	while (i < alcibiades->rsvps)
	{	
		alcibiades->plato[i].symposium_start = time;
//		printf("init_time: %zu\n", alcibiades->plato[i].symposium_start);
		fill_plato(&alcibiades->plato[i], argv,  alcibiades);
		alcibiades->plato[i].id = i + 1;
		alcibiades->plato[i].l_fork  = NULL;
		if (init_mutexes(&alcibiades->plato[i]) != 0)
		{
			printf("Init_mUtex error\n");
			return (EXIT_MUTEX_INIT_ERROR);
		}
		if (i < alcibiades->rsvps - 1)	
			alcibiades->plato[i].l_fork = &alcibiades->plato[i + 1].r_fork;
		else if (i == alcibiades->rsvps - 1)
			alcibiades->plato[i].l_fork = &alcibiades->plato[0].r_fork;
		if (pthread_create(&alcibiades->plato[i].thread, NULL, \
			&symp_routine, &alcibiades->plato[i]) != 0)
			return (EXIT_THREADS_ERROR);
//		print_structs(&alcibiades->plato[i]);
		i++;
	}
	/*printf("Before grim\n");
	if (pthread_create(&grim, NULL, &death_routine, &alcibiades) != 0)
	{
		printf("Inside grim thread\n");
		return (EXIT_THREADS_ERROR);
	}
	if (pthread_join(grim, NULL) != 0)
	{	
		printf("Thread Join Error\n");
		return (EXIT_FAILURE);
	}*/
	return (0);
}
/*
static int check_status(t_plato *plato, t_moniter *data)
{
	int i;

	i = 0;
// this is all nonsense as of this point	
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
*/
