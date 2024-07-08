/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:41:55 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/03 17:28:40 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"


static void	destroy_philo_mutexes(t_plato *plato)
{
	int i;

	i = 0;
	while (i < plato->data->rsvps)
	{
		pthread_mutex_destroy(&plato[i].meal_lock);
		i++;
	}
}
int init_mutexes(t_plato *plato, int rsvps)
{
	int i;

	i = 0;
	plato->r_fork = malloc(sizeof(pthread_mutex_t) * (rsvps));
	if (!plato->r_fork)
		return (1);
	while (i < rsvps)
	{
		if (pthread_mutex_init(plato->r_fork, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
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

void cleanup(t_plato *plato, t_data *data)
{
	destroy_fork_mutexes(plato);
	destroy_philo_mutexes(plato);
	free(plato);
	free(data);
}

int clean_data(t_data *data)
{
	free(data);
	printf("Data cleaned\n");
	return(1);
}
