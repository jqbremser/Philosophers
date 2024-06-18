/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:04:04 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/18 15:13:14 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

int init_data(t_data *data, char **argv)
{
	data->rsvps = anti_plato(argv[1]);
	data->hemlock_time = anti_plato(argv[2]);
	data->dinner_bell = anti_plato(argv[3]);
	data->drunken_stupor = anti_plato(argv[4]);
	if (argv[5])
		data->feasts = anti_plato(argv[5]);
	else
		data->feasts = -1;
	return (0);
}
