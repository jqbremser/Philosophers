/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:17:20 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 14:41:47 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"
#include <pthread.h>

static void *ostracize_socrates(t_philo *socrates)
{
	pthread_mutex_lock(&socrates->r_fork);
	print_message(RFORK, socrates);
	ft_usleep(socrates->hemlock_time);
	pthread_mutex_unlock(&socrates->r_fork);
	pthread_mutex_lock(&socrates->overseer->hemlock);
	socrates->overseer->hemlock_taken = true;
	pthread_mutex_unlock(&socrates->overseer->hemlock);
	return (NULL);
}
/*
void *death_routine(void *ptr)
{
	t_monitor *grim;
	int i;

	i = 0;
	grim = (t_monitor *)ptr;
	if (is_alive(grim->philo))
	{	
		printf("Grim Failed\n");
		print_message(DIED, grim->philo, 1);
	}
	return (0);
}*/

static int drink_wine(t_philo *philo)
{
	pthread_mutex_lock(&philo->overseer->hemlock);
	if (philo->overseer->hemlock_taken == true)
		return (1);
	pthread_mutex_unlock(&philo->overseer->hemlock);
	print_message(SLEEPING, philo);
	ft_usleep(philo->drunken_stupor);
	return (0);
}

static int eat(t_philo *philo)
{

	pthread_mutex_lock(&philo->overseer->hemlock);
	if (philo->overseer->hemlock_taken == true)
		return (1);
	pthread_mutex_unlock(&philo->overseer->hemlock);
	pthread_mutex_lock(&philo->r_fork);
	print_message(RFORK, philo);
	pthread_mutex_lock(philo->l_fork);
	print_message(LFORK, philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meal_time = update_krono(philo->overseer->symposium_start);
//	printf("meal_time: %zu\n", philo->meal_time);
	philo->meals_consumed++;
	print_message(EATING, philo); 
	ft_usleep(philo->dinner_bell);
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

void *symp_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->overseer->symposium_lock);
	pthread_mutex_unlock(&philo->overseer->symposium_lock);
	if (philo->overseer->rsvps == 1)
	{	
		printf("Single philo:\n");
		ostracize_socrates(philo);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->dinner_bell / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->overseer->hemlock);
		if (philo->overseer->hemlock_taken == true)
			break ;
		pthread_mutex_unlock(&philo->overseer->hemlock);
//		printf("Inside symp loop\n");
		if (eat(philo) == 1)
			break ;
		if (drink_wine(philo) == 1)
			break ;
		print_message(THINKING, philo);
	}
	return (0);
}
//		pthread_mutex_lock(philo->
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
