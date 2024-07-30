/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:39:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 15:37:05 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"


// static int join_threads(t_monitor *overseer)
// {
// 	int i;

// 	i = 0;
// 	printf("in join threads\n");
// 	while (i < overseer->rsvps)
// 	{
// 		if (pthread_join(overseer->philo[i].thread, NULL) != 0)
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	return (0);
// }

static int you_can_call_me_al(t_monitor *al)
{
	int i;
	size_t time;

	while (1)
	{	
		i = 0;
		if (al->full_philos >= al->rsvps)
		{
			printf("full filos\n");
			return (2);
		}
		while (i < al->rsvps)
		{	
			pthread_mutex_lock(&al->philo[i].meal_lock);
			time = 0;
			time = (kronosophize() - al->symposium_start - al->philo[i].meal_time);
			pthread_mutex_unlock(&al->philo[i].meal_lock);
			//			printf("Inside AL i: %d \n", i);
//			printf("symp:%zu\ncurr:%zu\nhem:%zu\n", al->philo[i].symposium_start, al->philo[i].current_time, al->philo[i].hemlock_time);
			if (time >= al->philo[i].hemlock_time)
			{
				pthread_mutex_lock(&al->hemlock);
				al->hemlock_taken = true;
				pthread_mutex_unlock(&al->hemlock);
				pthread_mutex_lock(&al->print_lock);
//				time = kronosophize() - (al->philo[i].symposium_start);
				printf("%zu %d %s\n", update_krono
						(al->symposium_start),  al->philo->id, DIED);
				pthread_mutex_unlock(&al->print_lock);
				return (1);
			}
			if (al->philo[i].feasts != -1)
			{
				pthread_mutex_lock(&al->philo[i].meal_lock);		
				if ((al->philo[i].meals_consumed >= al->philo[i].feasts) && !al->philo[i].full)
				{
//					printf("full_philosb4: %d\n", al->full_philos);
					al->full_philos++;
//					printf("full_philos: %d\n", al->full_philos);
					al->philo[i].full = true;
				}
				pthread_mutex_unlock(&al->philo[i].meal_lock);
			}
			i++;
		}
	}
	return (0);
}

static int terminate(t_monitor *overseer)
{
	int i;

	i = 0;
	if (overseer->philo == NULL || overseer == NULL)
		return (0);
	// join_threads(overseer);  WHEN DO I JOIN THREADS IF EVER?
	while (i < overseer->rsvps)
	{
		pthread_mutex_destroy(&overseer->philo[i].r_fork);
		pthread_mutex_destroy(&overseer->philo[i].meal_lock);
		overseer->philo[i].l_fork = NULL;
		overseer->philo[i].overseer = NULL;
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

int handle_error(int errno, t_monitor *overseer)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
		(void)!write(2, "Invalid amount of Args\n", 24);
	else if (errno == EXIT_INVALID_ARGS)
		(void)!write(2, "Invalid Arguments\n", 19);
	else if (errno == EXIT_PHILO_ERROR)
		(void)!write(2, "philo Error\n", 13);
	else if (errno == EXIT_INIT_ERROR)
	{
		if (overseer->philo != NULL)
			free(overseer->philo);
		(void)!write(2, "Error init monitor\n", 20);
		pthread_mutex_destroy(&overseer->symposium_lock);
		pthread_mutex_destroy(&overseer->hemlock);
		pthread_mutex_destroy(&overseer->print_lock);
	}
	else if (errno == EXIT_AL_ERROR)
		terminate(overseer);
	return (errno);
}

int main(int argc, char **argv)
{
	t_monitor overseer;

	if (argc != 5 && argc != 6)
		return (handle_error(EXIT_ARG_COUNT_ERROR, &overseer));
	if (check_args(argv) != 0)
		return (handle_error(EXIT_INVALID_ARGS, &overseer));
	if (init_monitor(&overseer, argv) != 0)
		return(handle_error(EXIT_INIT_ERROR, &overseer));
	if (init_philo(&overseer, argv) != 0)
		return (handle_error(EXIT_PHILO_ERROR, &overseer));
	if (you_can_call_me_al(&overseer) != 0)
		return (handle_error(EXIT_AL_ERROR, &overseer));	
	return (0);
}
