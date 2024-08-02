/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:36:19 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/02 15:01:44 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void dine_time(t_philo *philo)
{
  	// printf("inside dine_time\n");
    pthread_mutex_lock(&philo->meal_lock);
    // printf("symp_start: %ld\n", philo->overseer->symposium_start);
    // printf("meal_time before: %ld\n", philo->meal_time);
    philo->meal_time = (update_time() - philo->overseer->symposium_start) - philo->meal_time;
    // printf("meal_time after: %ld\n", philo->meal_time);
    philo->meals_consumed++;
    pthread_mutex_unlock(&philo->meal_lock);
    print_message(EATING, philo);
	ft_usleep(philo->time_to_eat, philo->overseer);
}

static int eat(t_philo *philo)
{
    if (hemlocked(philo->overseer))
        return (1);
    else
    {    
        pthread_mutex_lock(&philo->r_fork);
        print_message(RFORK, philo);   
    }
    if (hemlocked(philo->overseer))
    {
        pthread_mutex_unlock(&philo->r_fork); 
        return (1);
    }
    else
    {    
        pthread_mutex_lock(philo->l_fork);
        print_message(LFORK, philo);
    }
    if (hemlocked(philo->overseer))
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(&philo->r_fork); 
        return (1);
    }
    else    
    {
        dine_time(philo);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(&philo->r_fork);
    }
    return (0);
}

static int eep_eep(t_philo *philo)
{
    if (hemlocked(philo->overseer))
        return (1);
    // printf("inside eep_eep\n");
    print_message(SLEEPING, philo);
    ft_usleep(philo->time_to_sleep, philo->overseer);
    return (0);
}


static void ostracize_socrates(t_philo *socrates)
{
    pthread_mutex_lock(&socrates->r_fork);
	print_message(RFORK, socrates);
	ft_usleep(socrates->time_to_die, socrates->overseer);
	pthread_mutex_unlock(&socrates->r_fork);
    ostracize(socrates->overseer);
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
        return (ptr);
    }
    if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 10, philo->overseer);
    while (1)
    {
        if (eat(philo))
     {
        printf("EATBREAK\n");
            break ;
    }
        if (eep_eep(philo))
        {
            printf("EEPBREAK\n");
            break ;
        }
        print_message(THINKING, philo);
    }
    return (ptr);    
}