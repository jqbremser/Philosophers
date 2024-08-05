/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:36:19 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/03 22:33:31 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void	dine_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->meal_time = (update_time() - philo->overseer->symposium_start);
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_message(EATING, philo);
	ft_usleep(philo->time_to_eat, philo->overseer);
	unlock_forks(philo);
}

static int	eat(t_philo *philo)
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
		unlock_forks(philo);
		return (1);
	}
	else
		dine_time(philo);
	return (0);
}

static int	eep_eep(t_philo *philo)
{
	if (hemlocked(philo->overseer))
		return (1);
	print_message(SLEEPING, philo);
	ft_usleep(philo->time_to_sleep, philo->overseer);
	return (0);
}

static void	ostracize_socrates(t_philo *socrates)
{
	pthread_mutex_lock(&socrates->r_fork);
	print_message(RFORK, socrates);
	ft_usleep(socrates->time_to_die, socrates->overseer);
	pthread_mutex_unlock(&socrates->r_fork);
	ostracize(socrates->overseer);
}

void	*symp_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->overseer->symposium_lock);
	pthread_mutex_unlock(&philo->overseer->symposium_lock);
	if (philo->overseer->rsvps == 1)
	{
		ostracize_socrates(philo);
		return (ptr);
	}
	if (philo->id % 2 == 1)
	{
		print_message(THINKING, philo);
		ft_usleep(philo->time_to_eat / 10, philo->overseer);
	}
	while (1)
	{
		if (eat(philo))
			break ;
		if (eep_eep(philo))
			break ;
		print_message(THINKING, philo);
	}
	return (ptr);
}
