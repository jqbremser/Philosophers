/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:27:51 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/02 13:54:26 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static int monitering(t_moniter *al)
{
    int i;
    size_t time;
    int full_filos;

    while (1)
    {   
        i = 0;
        full_filos = 0;
        while (i < al->rsvps)
        {
            // printf("BEFORE, i: %d, id: %d, meal_time: %ld, time to die: %ld\n", i, al->philo[i].id, al->philo[i].meal_time , al->philo[i].time_to_die);
			time = update_time() - al->symposium_start; //time update problem
            pthread_mutex_lock(&al->philo[i].meal_lock);
            if (al->philo[i].meal_time >= al->philo[i].time_to_die)
			{
                // printf("Here, i: %d, id: %d, meal_time: %ld, time to die: %ld\n", i, al->philo[i].id, al->philo[i].meal_time , al->philo[i].time_to_die);
                ostracize(al);
				pthread_mutex_lock(&al->print_lock);
				printf("%zu %d %s\n", time, al->philo->id, DIED);
				pthread_mutex_unlock(&al->print_lock);
                pthread_mutex_unlock(&al->philo[i].meal_lock);
                return (1);
            }
            pthread_mutex_unlock(&al->philo[i].meal_lock);
            if (al->philo[i].feasts != -1)
            {
                pthread_mutex_lock(&al->philo[i].meal_lock);		
                if (al->philo[i].meals_consumed >= al->philo[i].feasts)
                    full_filos++;
                pthread_mutex_unlock(&al->philo[i].meal_lock);
            }
            i++;
        }
        if (full_filos >= al->rsvps)
        {
            ostracize(al);
            break ;
        }
    }
    return (0);
}

int init_threads_routine(t_moniter *overseer)
{
    int i;

    i = 0;
    pthread_mutex_lock(&overseer->symposium_lock);
    while (i < overseer->rsvps)
    {
        if (pthread_create(&overseer->philo[i].thread, NULL, &symp_routine, &overseer->philo[i]))
            return (EXIT_THREADS_ERROR);
        i++;
    }
    overseer->symposium_start = update_time();
    pthread_mutex_unlock(&overseer->symposium_lock);
    monitering(overseer);
    i = 0;
    while (i < overseer->rsvps)
    {
        if (pthread_join(overseer->philo[i].thread, NULL))
            return (EXIT_THREADS_ERROR); 
        i++;
    }
    return (0);
}