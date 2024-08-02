/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:33:46 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/01 18:44:09 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

static void tr_error_handle(t_moniter *overseer)
{
    int i;

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
	(void)!write(2, "Error init_philo moniter\n", 26);
}

static void philo_error_handle(t_moniter *overseer)
{
    int i;

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
	(void)!write(2, "Error init_philo moniter\n", 26);
}

static int handle_error(int errno, t_moniter *overseer)
{
    if (errno == EXIT_ARG_COUNT_ERROR)
	    (void)!write(2, "Invalid amount of Args\n", 24);
    else if (errno == EXIT_INVALID_ARGS)
 		(void)!write(2, "Invalid Arguments\n", 19);
    else if (errno == EXIT_MON_ERROR)
	{
		if (overseer->philo != NULL)
			free(overseer->philo);
		(void)!write(2, "Error init moniter\n", 20);
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

static int terminate(t_moniter *overseer)
{
	int i;

	i = 0;
	if (overseer->philo == NULL || overseer == NULL)
		return (0);
	while (i < overseer->rsvps)
	{
		pthread_mutex_destroy(&overseer->philo[i].r_fork);
		pthread_mutex_destroy(&overseer->philo[i].meal_lock);
		// overseer->philo[i].l_fork = NULL;
		// overseer->philo[i].overseer = NULL;
		i++;
	}
	pthread_mutex_destroy(&overseer->symposium_lock);
	pthread_mutex_destroy(&overseer->hemlock);
	pthread_mutex_destroy(&overseer->print_lock);
	free(overseer->philo);
	overseer->philo = NULL;
	printf(SOCRATES);
	return (0);
}

int main(int argc, char **argv)
{
    t_moniter   overseer;

    if (argc != 5 && argc != 6)
        return (handle_error(EXIT_ARG_COUNT_ERROR, &overseer));
    if (check_args(argv))
        return (handle_error(EXIT_INVALID_ARGS, &overseer));
    if (init_moniter(&overseer, argv))
        return (handle_error(EXIT_MON_ERROR, &overseer));
    if (init_philo(&overseer, argv))
        return (handle_error(EXIT_PHILO_ERROR, &overseer));
    if (init_threads_routine(&overseer))
        return (handle_error(EXIT_TR_ERROR, &overseer));
    terminate(&overseer);
    return (0);
}