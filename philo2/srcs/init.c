/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:04:04 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 14:40:37 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void fill_philo(t_philo *philo, char **argv, t_monitor *overseer)
{
//		memset(philo, 0, sizeof(t_philo));
		philo->overseer = overseer;
		philo->symposium_start = &overseer->symposium_start;
		philo->meal_time = 0;
		philo->hemlock_taken = &overseer->hemlock_taken;
		philo->hemlock_time = ft_atol(argv[2]);
		philo->dinner_bell = ft_atol(argv[3]);
		philo->drunken_stupor = ft_atol(argv[4]);
		if (argv[5])
			philo->feasts = ft_atol(argv[5]);
		else if (!argv[5])
			philo->feasts = -1;
}

int init_monitor(t_monitor *overseer, char **argv)
{
	overseer->philo = NULL;
	overseer->full_philos = 0;
	overseer->rsvps = ft_atol(argv[1]);
	overseer->hemlock_taken = false;
	overseer->all_fed = false;
	overseer->philo = malloc(sizeof(t_philo) * overseer->rsvps);
	if (overseer->philo == NULL)
		return (EXIT_MALLOC_FAIL);
	if (pthread_mutex_init(&overseer->hemlock, NULL) != 0)
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&overseer->print_lock, NULL) != 0)
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&overseer->symposium_lock, NULL) != 0)
		return (EXIT_MUTEX_INIT_ERROR);
	pthread_mutex_lock(&overseer->symposium_lock);
	return (0);
}

int init_philo(t_monitor *overseer, char **argv)
{
	int			i;
 //	pthread_t	grim;

	i = 0;
//	printf("start_time: %zu\n", time);
//	time = update_krono(time);
//	printf("updated_time: %zu\n", time);
	while (i < overseer->rsvps)
	{	
//		printf("init_time: %zu\n", overseer->philo[i].symposium_start);
		fill_philo(&overseer->philo[i], argv,  overseer);
		overseer->philo[i].id = i + 1;
		overseer->philo[i].l_fork  = NULL;
		if (init_mutexes(&overseer->philo[i]) != 0)
		{
			printf("Init_mUtex error\n");
			return (EXIT_MUTEX_INIT_ERROR);
		}
		if (i < overseer->rsvps - 1)	
			overseer->philo[i].l_fork = &overseer->philo[i + 1].r_fork;
		else if (i == overseer->rsvps - 1)
			overseer->philo[i].l_fork = &overseer->philo[0].r_fork;
		if (pthread_create(&overseer->philo[i].thread, NULL, \
			&symp_routine, &overseer->philo[i]) != 0)
			return (EXIT_THREADS_ERROR);
//		print_structs(&overseer->philo[i]);
		i++;
	}
	overseer->symposium_start = kronosophize();
	pthread_mutex_unlock(&overseer->symposium_lock);	
	return (0);
}
	/*printf("Before grim\n");
	if (pthread_create(&grim, NULL, &death_routine, &overseer) != 0)
	{
		printf("Inside grim thread\n");
		return (EXIT_THREADS_ERROR);
	}
	if (pthread_join(grim, NULL) != 0)
	{	
		printf("Thread Join Error\n");
		return (EXIT_FAILURE);
	}*/
/*
static int check_status(t_philo *philo, t_monitor *data)
{
	int i;

	i = 0;
// this is all nonsense as of this point	
	while (i <= data->rsvps)
	{
		if (philo->id == i)
		{
			if (philo->hemlock == true)
			{
				printf("Philo %d has died at %zu\n", philo->id, data->current_time);
				return (1);
			}
			if (data->feasts > 0)
			{	if (philo->meals_consumed > data->feasts)
				{
					printf("Philo %d is full\n", philo->id); 
					return (2);
				}
			}
		}
	i++;
	}
	return (0);
}
*/
