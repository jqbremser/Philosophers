/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:17:20 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/15 20:22:00 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void *ostracize_socrates(t_plato *socrates)
{
	pthread_mutex_lock(&socrates->r_fork);
	print_message(FORK, socrates, 0);
	ft_usleep(socrates->hemlock_time);
	pthread_mutex_unlock(&socrates->r_fork);
	pthread_mutex_lock(&socrates->alcibiades->hemlock);
	socrates->hemlock_taken = true;
	pthread_mutex_unlock(&socrates->alcibiades->hemlock);
	return (NULL);
}
 

void *symp_routine(void *ptr)
{
	t_moniter *alcibiades;

	alcibiades = (t_moniter *)ptr;
	if (alcibiades->rsvps == 1)
		return(ostracize_socrates(alcibiades->plato[0]));
	if (!is_alive(alcibiades->plato[0]))
		print_message(DIED, alcibiades->plato[0], 1);
	// incomplete so far
//	if (check_status(alcibiades->plato, alcibiades) == 1)
//		break ;
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
