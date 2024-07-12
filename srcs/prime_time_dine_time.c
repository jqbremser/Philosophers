/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_time_dine_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:39:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/12 15:31:59 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"


int handle_error(int errno, t_moniter *alcibiades)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
		(void)!write(2, "Invalid amount of Args\n", 24);
	else if (errno == EXIT_INVALID_ARGS)
		(void)!write(2, "Invalid Arguments\n", 19);
	else if (errno == EXIT_INIT_ERROR)
	{
		if (alcibiades->plato != NULL)
			free(alcibiades->plato);
		(void)!write(2, "Error init moniter\n", 20);
	}
	return (errno);
}

int main(int argc, char **argv)
{
	t_moniter alcibiades;

	if (argc != 5 && argc != 6)
		return (handle_error(EXIT_ARG_COUNT_ERROR, &alcibiades));
	if (check_args(argv) != 0)
		return (handle_error(EXIT_INVALID_ARGS, &alcibiades));
	if (init_moniter(&alcibiades, argv) != 0)
		return(handle_error(EXIT_INIT_ERROR, &alcibiades));
	if (init_plato(alcibiades.plato, argv, &alcibiades) != 0)
		return (handle_error(EXIT_INIT_ERROR, &alcibiades));
	print_structs(&alcibiades, alcibiades.plato);
	return (0);
}
