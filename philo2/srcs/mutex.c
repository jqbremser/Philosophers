/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:41:55 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 13:39:27 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"
#include <pthread.h>


int init_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->r_fork, NULL) != 0)
			return (1);
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
			return (1);
	return (0);
}

/*

   static void	destroy_philo_mutexes(t_philo *philo)
   {
   int i;

   i = 0;
   while (i < philo->overseer->rsvps)
   {
   pthread_mutex_destroy(&philo[i].meal_lock);
   i++;
   }
   }

int destroy_fork_mutexes(t_philo* philo)
{
	t_philo	tmp;

	tmp = *philo;
	pthread_mutex_destroy(tmp.r_fork);
	free(tmp.r_fork);
	tmp.r_fork = NULL;
	return(0);
}

void cleanup(t_philo *philo, t_moniter *data)
{
	destroy_fork_mutexes(philo);
	destroy_philo_mutexes(philo);
	free(philo);
	free(data);
}

int clean_data(t_moniter *data)
{
	free(data);
	printf("Data cleaned\n");
	return(1);
}*/
