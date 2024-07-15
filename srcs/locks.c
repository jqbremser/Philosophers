/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:32 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/15 19:53:50 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"


int is_alive(t_plato *plato)
{
	int alive;

	pthread_mutex_lock(&plato->alcibiades->hemlock);
	if (plato->hemlock_taken == true)
	{
		plato->alcibiades->hemlock_taken = true;
		alive = 0;
	}
	else
	{
		plato->alcibiades->hemlock_taken = false;
		alive = 1;
	}
	pthread_mutex_unlock(&plato->alcibiades->hemlock);
	return (alive);
}
			
void print_message(const char *message, t_plato *plato, int dead)
{
	unsigned int time;

	if (!is_alive(plato) && dead != 1)
		return ;
	time = update_krono(plato->symposium_start);
	pthread_mutex_lock(&plato->alcibiades->print_lock);
	printf("%u %d %s\n", time, plato->id, message);
	pthread_mutex_unlock(&plato->alcibiades->print_lock);
}
