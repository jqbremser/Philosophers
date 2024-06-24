/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:04:04 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/24 17:16:51 by jbremser         ###   ########.fr       */
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
	data->symposium_start = kronosophize();
	ft_usleep(100);
	data->current_time = update_krono(data->symposium_start);
	if (init_mutexes(data) != 0)
	{
		destroy_data_mutexes(data);
		printf("Error inititalizing data mutexes\n");
		return (0);
	}
	return (1);
}

int init_plato(t_plato *plato, t_data data)
{
	int i;

	i = 0;

	while (i < data.rsvps)
	{
		memset(&plato[i], 0, sizeof(t_plato));
		plato[i].id = i + 1;
		plato[i].data = &data;
		i++;
	}
	return (1);
}

int destroy_data_mutexes(t_data *data)
{
	int		i;
	t_data	tmp;

	i = 0;
	tmp = *data;
	while (i < tmp.num_of_philos)
	{
		pthread_mutex_destroy(&tmp.forks[i]);
		i++;
	}
	free(data->forks);
	return(1);
}

int init_mutexes(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->rsvps));
	if (!data->forks)
		return (1);
	while (i < data.rsvps)
	{
		if (pthread_mutex_int(&data.forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
