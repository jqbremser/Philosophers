/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:32 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/25 16:19:08 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"


int is_alive(t_plato *plato)
{
	int alive;

	pthread_mutex_lock(&plato->alcibiades->hemlock);
	if (*plato->hemlock_taken == true)
		alive = 0;
	else
		alive = 1;
	pthread_mutex_unlock(&plato->alcibiades->hemlock);
	return (alive);
}
			
int print_message(const char *message, t_plato *plato)
{
	unsigned int time;

	pthread_mutex_lock(&plato->alcibiades->hemlock);
	if (plato->alcibiades->hemlock_taken == true)
		return (1);
	pthread_mutex_unlock(&plato->alcibiades->hemlock);
	time = kronosophize() - (plato->symposium_start);
	pthread_mutex_lock(&plato->alcibiades->print_lock);
	printf("%u %d %s\n", time, plato->id, message);
	pthread_mutex_unlock(&plato->alcibiades->print_lock);
	return (0);
}

