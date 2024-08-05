/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:27:51 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/05 14:23:15 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

extern char *philosopher_names[400];

static int	monitor(t_monitor *al, int i, int full_filos)
{	
	const char *philosopher_name;
	const char *philosopher_quotes;
	size_t	time;

	time = update_time() - al->symposium_start;
	pthread_mutex_lock(&al->philo[i].meal_lock);
	if (time - al->philo[i].meal_time >= al->philo[i].time_to_die)
	{
		pthread_mutex_unlock(&al->philo[i].meal_lock);
		ostracize(al);
		pthread_mutex_lock(&al->print_lock);
		philosopher_name = philosopher_names[al->philo[i].id - 1]; // Adjust index for 0-based array
		philosopher_quotes = philosopher_names[(al->philo[i].id - 1) + 200]; // Adjust index for 0-based array
		printf("%zu %s %s\n%s\n", time, philosopher_name, DIED, philosopher_quotes);
		pthread_mutex_unlock(&al->print_lock);
		return (-1);
	}
	pthread_mutex_unlock(&al->philo[i].meal_lock);
	if (al->philo[i].feasts != -1)
	{
		pthread_mutex_lock(&al->philo[i].meal_lock);
		if (al->philo[i].meals_consumed >= al->philo[i].feasts)
			full_filos++;
		pthread_mutex_unlock(&al->philo[i].meal_lock);
	}
	return (full_filos);
}

static int	monitoring(t_monitor *al)
{
	int		i;
	int		full_filos;

	while (1)
	{
		i = 0;
		full_filos = 0;
		while (i < al->rsvps)
		{
			full_filos = (monitor(al, i, full_filos));
			if (full_filos == -1)
				return (1);
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

int	init_threads_routine(t_monitor *al)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&al->symposium_lock);
	while (i < al->rsvps)
	{
		if (pthread_create(&al->philo[i].thread,
				NULL, &symp_routine, &al->philo[i]))
			return (EXIT_THREADS_ERROR);
		i++;
	}
	al->symposium_start = update_time();
	pthread_mutex_unlock(&al->symposium_lock);
	monitoring(al);
	i = 0;
	while (i < al->rsvps)
	{
		if (pthread_join(al->philo[i].thread, NULL))
			return (EXIT_THREADS_ERROR);
		i++;
	}
	return (0);
}
