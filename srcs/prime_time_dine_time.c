/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:39:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/25 18:57:16 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

int handle_error(int errno, t_moniter *alcibiades)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
		(void)!write(2, "Invalid amount of Args\n", 24);
	else if (errno == EXIT_INVALID_ARGS)
		(void)!write(2, "Invalid Arguments\n", 19);
	else if (errno == EXIT_PLATO_ERROR)
		(void)!write(2, "Plato Error\n", 13);
	else if (errno == EXIT_INIT_ERROR)
	{
		if (alcibiades->plato != NULL)
			free(alcibiades->plato);
		(void)!write(2, "Error init moniter\n", 20);
	}
	return (errno);
}

static int join_threads(t_moniter *alcibiades)
{
	int i;

	i = 0;
	while (i < alcibiades->rsvps)
	{
		if (pthread_join(alcibiades->plato[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}

static int you_can_call_me_al(t_moniter *al)
{
	int i;
	size_t time;

	while (1)
	{	
		al->full_philos = 0;
		i = 0;
		while (i < al->rsvps)
		{
			time = (update_krono(al->plato[i].symposium_start) - al->plato[i].meal_time);
//			printf("Inside AL i: %d \n", i);
//			printf("symp:%zu\ncurr:%zu\nhem:%zu\n", al->plato[i].symposium_start, al->plato[i].current_time, al->plato[i].hemlock_time);
			if (time >= al->plato[i].hemlock_time)
			{
//				printf("DEATH:");
				pthread_mutex_lock(&al->hemlock);
				al->hemlock_taken = true;
				pthread_mutex_unlock(&al->hemlock);
				pthread_mutex_lock(&al->print_lock);
//				time = kronosophize() - (al->plato[i].symposium_start);
				printf("%zu %d %s\n", update_krono
						(al->plato[i].symposium_start),  al->plato->id, DIED);
				pthread_mutex_unlock(&al->print_lock);
				return (1);
			}
			if (al->plato[i].feasts != -1)
			{
				if (al->plato[i].meals_consumed >= al->plato[i].feasts)
				{ 
					pthread_mutex_lock(&al->plato[i].meal_lock);		
					al->full_philos++;
					pthread_mutex_unlock(&al->plato[i].meal_lock);		
				}
			}
			i++;
		}
	}
	return (0);
}

//void terminate(t_moniter *alcibiades)
//{
//
//}

int main(int argc, char **argv)
{
	t_moniter alcibiades;

	if (argc != 5 && argc != 6)
		return (handle_error(EXIT_ARG_COUNT_ERROR, &alcibiades));
	if (check_args(argv) != 0)
		return (handle_error(EXIT_INVALID_ARGS, &alcibiades));
	if (init_moniter(&alcibiades, argv) != 0)
		return(handle_error(EXIT_INIT_ERROR, &alcibiades));
	if (init_plato(&alcibiades, argv) != 0)
		return (handle_error(EXIT_PLATO_ERROR, &alcibiades));
	if (you_can_call_me_al(&alcibiades) != 0)
		return (handle_error(EXIT_THREADS_ERROR, &alcibiades));	
	if (join_threads(&alcibiades) != 0)
		return (handle_error(EXIT_THREADS_ERROR, &alcibiades));
//	terminate(&alcibiades);
	return (0);
}
