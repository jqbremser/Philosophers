/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:17:20 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/25 18:51:26 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"
#include <pthread.h>

static void *ostracize_socrates(t_plato *socrates)
{
	pthread_mutex_lock(&socrates->r_fork);
	print_message(RFORK, socrates);
	ft_usleep(socrates->hemlock_time);
	pthread_mutex_unlock(&socrates->r_fork);
	pthread_mutex_lock(&socrates->alcibiades->hemlock);
	socrates->alcibiades->hemlock_taken = true;
	pthread_mutex_unlock(&socrates->alcibiades->hemlock);
	return (NULL);
}
/*
void *death_routine(void *ptr)
{
	t_moniter *grim;
	int i;

	i = 0;
	grim = (t_moniter *)ptr;
	if (is_alive(grim->plato))
	{	
		printf("Grim Failed\n");
		print_message(DIED, grim->plato, 1);
	}
	return (0);
}*/

static int drink_wine(t_plato *plato)
{
	pthread_mutex_lock(&plato->alcibiades->hemlock);
	if (plato->alcibiades->hemlock_taken == true)
		return (1);
	pthread_mutex_unlock(&plato->alcibiades->hemlock);
	print_message(SLEEPING, plato);
	ft_usleep(plato->drunken_stupor);
	return (0);
}

static int eat(t_plato *plato)
{

	pthread_mutex_lock(&plato->alcibiades->hemlock);
	if (plato->alcibiades->hemlock_taken == true)
		return (1);
	pthread_mutex_unlock(&plato->alcibiades->hemlock);
	pthread_mutex_lock(&plato->r_fork);
	print_message(RFORK, plato);
	pthread_mutex_lock(plato->l_fork);
	print_message(LFORK, plato);
	pthread_mutex_lock(&plato->meal_lock);
	plato->meal_time = update_krono(plato->symposium_start);
	printf("meal_time: %zu\n", plato->meal_time);
	plato->meals_consumed++;
	print_message(EATING, plato); 
	ft_usleep(plato->dinner_bell);
	pthread_mutex_unlock(&plato->meal_lock);
	pthread_mutex_unlock(&plato->r_fork);
	pthread_mutex_unlock(plato->l_fork);
	return (0);
}

void *symp_routine(void *ptr)
{
	t_plato *plato;

	plato = (t_plato *)ptr;
	if (plato->alcibiades->rsvps == 1)
	{	
		printf("Single Plato:\n");
		ostracize_socrates(plato);
	}
	if (plato->id % 2 == 0)
		ft_usleep(plato->dinner_bell / 10);
	while (1)
	{
//		printf("Inside symp loop\n");
		if (eat(plato) == 1)
			break ;
		if (drink_wine(plato) == 1)
			break ;
		print_message(THINKING, plato);
	}
	return (0);
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
