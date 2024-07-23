/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:17:20 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/23 18:44:48 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"
#include <pthread.h>

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

void *death_routine(void *ptr)
{
	t_moniter *grim;
	int i;

	i = 0;
	grim = (t_moniter *)ptr;
	if (is_alive(grim->plato))
		print_message(DIED, grim->plato, 1);

	return (0);
}

void drink_wine(t_plato *plato)
{
	ft_usleep(plato->drunken_stupor);
	print_message(SLEEPING, plato, 0);
}

void eat(t_plato *plato)
{
	pthread_mutex_lock(&plato->r_fork);
	print_message(FORK, plato, 0);
	pthread_mutex_unlock(&plato->r_fork);
	pthread_mutex_lock(plato->l_fork);
	print_message(FORK, plato, 0);
	pthread_mutex_unlock(plato->l_fork);
	pthread_mutex_lock(&plato->meal_lock);
	plato->meal_time = kronosophize();
	plato->meals_consumed++;
	ft_usleep(plato->dinner_bell);
	pthread_mutex_unlock(&plato->meal_lock);
	print_message(EATING, plato, 0); 
}


void *symp_routine(void *ptr)
{
	t_plato *plato;

	plato = (t_plato *)ptr;
	if (plato->alcibiades->rsvps == 1)
	{	
		printf("Here");
		return(ostracize_socrates(plato));
	}
		// incomplete so far
//	if (check_status(alcibiades->plato, alcibiades) == 1)
//		break ;
	if (plato->id % 2 == 0)
		ft_usleep(plato->dinner_bell / 2);
	while (1)
	{
		printf("Inside inf loop");
		eat(plato);
		drink_wine(plato);

	}
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
