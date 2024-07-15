/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:41:55 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/15 20:19:39 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"
#include <pthread.h>


int init_mutexes(t_plato *plato)
{
	if (pthread_mutex_init(&plato->r_fork, NULL) != 0)
			return (1);
	if (pthread_mutex_init(&plato->meal_lock, NULL) != 0)
			return (1);
	return (0);
}

/*

   static void	destroy_philo_mutexes(t_plato *plato)
   {
   int i;

   i = 0;
   while (i < plato->alcibiades->rsvps)
   {
   pthread_mutex_destroy(&plato[i].meal_lock);
   i++;
   }
   }

int destroy_fork_mutexes(t_plato* plato)
{
	t_plato	tmp;

	tmp = *plato;
	pthread_mutex_destroy(tmp.r_fork);
	free(tmp.r_fork);
	tmp.r_fork = NULL;
	return(0);
}

void cleanup(t_plato *plato, t_moniter *data)
{
	destroy_fork_mutexes(plato);
	destroy_philo_mutexes(plato);
	free(plato);
	free(data);
}

int clean_data(t_moniter *data)
{
	free(data);
	printf("Data cleaned\n");
	return(1);
}*/
