/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:41:54 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/05 14:45:23 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void	tr_error_handle(t_monitor *overseer)
{
	int	i;

	i = 0;
	if (overseer->philo != NULL)
		free(overseer->philo);
	pthread_mutex_destroy(&overseer->symposium_lock);
	pthread_mutex_destroy(&overseer->hemlock);
	pthread_mutex_destroy(&overseer->print_lock);
	while (i < overseer->rsvps)
	{
		pthread_mutex_destroy(&overseer->philo[i].r_fork);
		pthread_mutex_destroy(&overseer->philo[i].meal_lock);
		pthread_join(overseer->philo[i].thread, NULL);
		i++;
	}
	(void)!write(2, "Error init_philo monitor\n", 26);
}

static void	philo_error_handle(t_monitor *overseer)
{
	int	i;

	i = 0;
	if (overseer->philo != NULL)
		free(overseer->philo);
	pthread_mutex_destroy(&overseer->symposium_lock);
	pthread_mutex_destroy(&overseer->hemlock);
	pthread_mutex_destroy(&overseer->print_lock);
	while (i < overseer->rsvps)
	{
		pthread_mutex_destroy(&overseer->philo[i].r_fork);
		pthread_mutex_destroy(&overseer->philo[i].meal_lock);
		i++;
	}
	(void)!write(2, "Error init_philo monitor\n", 26);
}

int	handle_error(int errno, t_monitor *overseer)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
		(void)!write(2, "Invalid amount of Args\n", 24);
	else if (errno == EXIT_INVALID_ARGS)
		(void)!write(2, "Invalid Arguments\n", 19);
	else if (errno == EXIT_MON_ERROR)
	{
		if (overseer->philo != NULL)
			free(overseer->philo);
		(void)!write(2, "Error init monitor\n", 20);
		pthread_mutex_destroy(&overseer->symposium_lock);
		pthread_mutex_destroy(&overseer->hemlock);
		pthread_mutex_destroy(&overseer->print_lock);
	}
	else if (errno == EXIT_PHILO_ERROR)
		philo_error_handle(overseer);
	else if (errno == EXIT_TR_ERROR)
		tr_error_handle(overseer);
	return (0);
}

int	terminate(t_monitor *overseer)
{
	int	i;

	i = 0;
	if (overseer->philo == NULL || overseer == NULL)
		return (0);
	while (i < overseer->rsvps)
	{
		pthread_mutex_destroy(&overseer->philo[i].r_fork);
		pthread_mutex_destroy(&overseer->philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&overseer->symposium_lock);
	pthread_mutex_destroy(&overseer->hemlock);
	pthread_mutex_destroy(&overseer->print_lock);
	free(overseer->philo);
	overseer->philo = NULL;
	return (0);
}
