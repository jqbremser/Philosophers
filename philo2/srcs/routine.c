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

static void *ostracize_socrates(t_philo *socrates)
{
	pthread_mutex_lock(&socrates->r_fork);
	print_message(RFORK, socrates);
	ft_usleep(socrates->hemlock_time, socrates->overseer);
	pthread_mutex_unlock(&socrates->r_fork);
	pthread_mutex_lock(&socrates->overseer->hemlock);
	socrates->overseer->hemlock_taken = true;
	pthread_mutex_unlock(&socrates->overseer->hemlock);
	return (NULL);
}

void ostracize(t_moniter *al)
{
	pthread_mutex_lock(&al->hemlock);
	al->hemlock_taken = true;
	pthread_mutex_unlock(&al->hemlock);
}

int hemlocked(t_moniter *overseer)
{
	pthread_mutex_lock(&overseer->hemlock);
	if (overseer->hemlock_taken)
		{
		pthread_mutex_unlock(&overseer->hemlock);
		// printf("HEMLOCKED\n");
		return (1);
		}
	pthread_mutex_unlock(&overseer->hemlock);
	return (0);
}

static int drink_wine(t_philo *philo)
{
	if (hemlocked(philo->overseer))
		return (1);	
	print_message(SLEEPING, philo);
	ft_usleep(philo->drunken_stupor, philo->overseer);
	return (0);
}

static int dine_time(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->meal_lock) != 0)
		return (1);
	philo->meal_time = kronosophize() - philo->overseer->symposium_start;
	if (pthread_mutex_unlock(&philo->meal_lock) != 0)
		return (1);
	philo->meals_consumed++;
	print_message(EATING, philo);
	ft_usleep(philo->dinner_bell, philo->overseer);
	// else
		// return (1);		
	return(0);
}

int is_full(t_moniter *al)
{
	pthread_mutex_lock(&al->symposium_lock);		
	if (al->full_philos >= al->rsvps)
	{
		al->all_fed = true;
		pthread_mutex_unlock(&al->symposium_lock);
		return (1);
	}
	pthread_mutex_unlock(&al->symposium_lock);
	return (0);
}

static int therefore_i_am(t_philo *philo, pthread_mutex_t *rfork, pthread_mutex_t *lfork)
{
	if ((hemlocked(philo->overseer)) || (is_full(philo->overseer)))
	{
		if (rfork)
			pthread_mutex_unlock(&philo->r_fork);
		if (lfork)
			pthread_mutex_unlock(philo->l_fork);
		// printf("Inside therefore_i_am\n");
		return (1);
	}
	return (0);
}

static int eat(t_philo *philo)
{
 	if (therefore_i_am(philo, NULL, NULL))
 		return (1);
	if (pthread_mutex_lock(&philo->r_fork) == 0)
	{
 		if (therefore_i_am(philo, &philo->r_fork, NULL))
 			return (1);	
		print_message(RFORK, philo);
		if (pthread_mutex_lock(philo->l_fork) == 0)
		{
			if (therefore_i_am(philo, &philo->r_fork, philo->l_fork))
 				return (1);	
			print_message(LFORK, philo);
			if (dine_time(philo) == 0)
			{
				if (!(pthread_mutex_unlock(&philo->r_fork)) && !(pthread_mutex_unlock(philo->l_fork)))
					return (0);
			}
			// else if (dine_time(philo) == 1)
			// 	return (1);
		}
		else
		{
			pthread_mutex_unlock(&philo->r_fork);
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

void *symp_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->overseer->symposium_lock); //syncronizer
	pthread_mutex_unlock(&philo->overseer->symposium_lock);
	if (philo->overseer->rsvps == 1)
	{	
		ostracize_socrates(philo);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->dinner_bell / 10, philo->overseer);
	while (!therefore_i_am(philo, NULL, NULL))
	{
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


// static int eat(t_philo *philo)
// {
// 	if (hemlocked(&philo->overseer) != 0)
// 		return (1);
// 	if (pthread_mutex_lock(&philo->r_fork) != 0)
// 		return (1);   //if fails return 1;
// 	print_message(RFORK, philo);
// 	if (pthread_mutex_lock(philo->l_fork) != 0)
// 		return (1); //check if it has right fork, before picking up, if fails return 1; and if it fails while holding rfork, drop(unlock mutex) the right fork
// 	print_message(LFORK, philo);
// 	//ONCE THE PHILO HAS PICKED UP TWO FORKS, then and only then can he eat. 
// 	pthread_mutex_lock(&philo->meal_lock);
// 	philo->meal_time = update_krono(philo->overseer->symposium_start);
// //	printf("meal_time: %zu\n", philo->meal_time);
// 	philo->meals_consumed++;
// 	print_message(EATING, philo); 
// 	ft_usleep(philo->dinner_bell);
// 	pthread_mutex_unlock(&philo->meal_lock);
// 	pthread_mutex_unlock(&philo->r_fork);  //a new helper function to drop the forks when eating is completing, and this will be the part that will unlock the lrfork mutexes
// 	pthread_mutex_unlock(philo->l_fork);
// 	return (0);
// // }