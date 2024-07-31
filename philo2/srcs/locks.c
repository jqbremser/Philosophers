/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:32 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 14:42:13 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

int is_alive(t_philo *philo)
{
	int alive;

	pthread_mutex_lock(&philo->overseer->hemlock);
	if (*philo->hemlock_taken == true)
		alive = 0;
	else
		alive = 1;
	pthread_mutex_unlock(&philo->overseer->hemlock);
	return (alive);
}
			
int print_message(const char *message, t_philo *philo)
{
	unsigned int time;
	
	// printf("hemlocked: %i, is_full: %i \n", hemlocked(philo->overseer), is_full(philo->overseer));
	if (hemlocked(philo->overseer) || (is_full(philo->overseer)))
		{
		// printf("Hemlocked\n");	
		return (1);
		}
	time = kronosophize() - (philo->overseer->symposium_start);
	pthread_mutex_lock(&philo->overseer->print_lock);
	printf("%u %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->overseer->print_lock);
	return (0);
}