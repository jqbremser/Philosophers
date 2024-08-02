/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:48:58 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/02 15:06:19 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

int print_message(const char *message, t_philo *philo)
{
    unsigned int time;

    if (hemlocked(philo->overseer))
        return (1);
    time = (update_time() - philo->overseer->symposium_start);
    pthread_mutex_lock(&philo->overseer->print_lock);
	printf("%u %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->overseer->print_lock);
    return (0);
}

void ostracize(t_moniter *overseer)
{
	pthread_mutex_lock(&overseer->hemlock);
	overseer->hemlock_taken = true;
	pthread_mutex_unlock(&overseer->hemlock);
}

int hemlocked(t_moniter *overseer)
{
    pthread_mutex_lock(&overseer->hemlock);
    if (overseer->hemlock_taken)
    {
        pthread_mutex_unlock(&overseer->hemlock);
        // printf("Hemlocked returning 1\n");
        return (1);
    }
    pthread_mutex_unlock(&overseer->hemlock);
    return (0);
}