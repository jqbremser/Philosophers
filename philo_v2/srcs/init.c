/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:12:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/02 14:19:28 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void print_structs(t_philo *philo)
{
	printf("\nPHILO ID:%d\n", philo->id);
	printf("rsvps:%d\n", philo->overseer->rsvps);
	printf("hemlock_time:%zu\n", philo->time_to_die);
	printf("Eat:%ld\n", philo->time_to_eat);
	printf("Sleep:%ld\n", philo->time_to_sleep);
	printf("Feasts:%d\n", philo->feasts);
	printf("Start of Symposium:%zu\n", philo->overseer->symposium_start);
	printf("Meals consumed: %d\n\n", philo->meals_consumed);
}

static void fill_philo(t_philo *philo, char **argv, t_moniter *overseer)
{
 	philo->overseer = overseer;
	philo->symposium_start = &overseer->symposium_start;
	philo->meal_time = 0;
	philo->hemlock_taken = &overseer->hemlock_taken;
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->feasts = ft_atol(argv[5]);
	else if (!argv[5])
		philo->feasts = -1;   
}

int init_philo(t_moniter *overseer, char **argv)
{
    int i;

    i = 0;
    while (i < overseer->rsvps)
    {
        overseer->philo[i].id = i + 1;
        overseer->philo[i].l_fork = NULL;
        if (pthread_mutex_init(&overseer->philo->r_fork, NULL))
			return (1);
	    if (pthread_mutex_init(&overseer->philo->meal_lock, NULL))
			return (1);
        if (i < overseer->rsvps - 1)	
			overseer->philo[i].l_fork = &overseer->philo[i + 1].r_fork;
		else if (i == overseer->rsvps - 1)
			overseer->philo[i].l_fork = &overseer->philo[0].r_fork;
   		fill_philo(&overseer->philo[i], argv,  overseer);
		print_structs(&overseer->philo[i]);
		i++;
    }
    return (0);
}

int init_moniter(t_moniter *overseer, char **argv)
{
    overseer->philo = NULL;
    overseer->full_philos = 0;
    overseer->rsvps = ft_atol(argv[1]);
    overseer->hemlock_taken = false;
    overseer->philo = malloc(sizeof(t_philo) * overseer->rsvps);
	overseer->symposium_start = 0;
	if (overseer->philo == NULL)
		return (EXIT_MALLOC_FAIL);
    if (pthread_mutex_init(&overseer->hemlock, NULL))
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&overseer->print_lock, NULL))
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&overseer->symposium_lock, NULL))
		return (EXIT_MUTEX_INIT_ERROR);
    return (0);
}