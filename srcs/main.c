/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:33:46 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/05 14:43:20 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

int	main(int argc, char **argv)
{
	t_monitor	overseer;

	if (argc != 5 && argc != 6)
		return (handle_error(EXIT_ARG_COUNT_ERROR, &overseer));
	if (check_args(argv))
		return (handle_error(EXIT_INVALID_ARGS, &overseer));
	if (init_monitor(&overseer, argv))
		return (handle_error(EXIT_MON_ERROR, &overseer));
	if (init_philo(&overseer, argv))
		return (handle_error(EXIT_PHILO_ERROR, &overseer));
	if (init_threads_routine(&overseer))
		return (handle_error(EXIT_TR_ERROR, &overseer));
	terminate(&overseer);
	return (0);
}
