/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:17:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/18 15:17:20 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMPOSIUM_H
# define SYMPOSIUM_H
#include <stdlib.h>
#include <stdio.h>
# define FT_LONG_MAX 9223372036854775807L

typedef struct s_data
{
	int rsvps;
	int hemlock_time;
	int	dinner_bell;
	int	drunken_stupor;
	int feasts;
}	t_data;

/* ************************************************************************** */
/*									philo_toolkit							  */
/* ************************************************************************** */
int anti_plato(char *str);
int	isdigit(int c);
/* ************************************************************************** */
/*									init									  */
/* ************************************************************************** */
int init_data(t_data *data, char **argv);

#endif
