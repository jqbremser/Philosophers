/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:12:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/03 22:31:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void	fill_philo(t_philo *philo, char **argv, t_monitor *overseer)
{
	philo->overseer = overseer;
	philo->symposium_start = &overseer->symposium_start;
	philo->meal_time = 0;
	philo->hemlock_taken = &overseer->hemlock_taken;
	philo->meals_consumed = 0;
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->feasts = ft_atol(argv[5]);
	else if (!argv[5])
		philo->feasts = -1;
}

int	init_philo(t_monitor *overseer, char **argv)
{
	int	i;

	i = 0;
	while (i < overseer->rsvps)
	{
		overseer->philo[i].id = i + 1;
		overseer->philo[i].l_fork = NULL;
		if (pthread_mutex_init(&overseer->philo[i].r_fork, NULL))
			return (1);
		if (pthread_mutex_init(&overseer->philo[i].meal_lock, NULL))
			return (1);
		if (i < overseer->rsvps - 1)
			overseer->philo[i].l_fork = &overseer->philo[i + 1].r_fork;
		else if (i == overseer->rsvps - 1)
			overseer->philo[i].l_fork = &overseer->philo[0].r_fork;
		fill_philo(&overseer->philo[i], argv, overseer);
		i++;
	}
	if (overseer->rsvps == 1)
		overseer->philo[0].l_fork = NULL;
	return (0);
}

int	init_monitor(t_monitor *overseer, char **argv)
{
	overseer->philo = NULL;
	overseer->full_philos = 0;
	overseer->rsvps = ft_atol(argv[1]);
	overseer->hemlock_taken = false;
	overseer->philo = malloc(sizeof(t_philo) * overseer->rsvps);
	overseer->symposium_start = 0;
	if (overseer->philo == NULL)
		return (EXIT_MALLOC_FAIL);
	if (pthread_mutex_init(&overseer->hemlock, NULL))
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&overseer->print_lock, NULL))
		return (EXIT_MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&overseer->symposium_lock, NULL))
		return (EXIT_MUTEX_INIT_ERROR);
	return (0);
}
