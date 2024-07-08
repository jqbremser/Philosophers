/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:17:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/08 14:47:32 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMPOSIUM_H
# define SYMPOSIUM_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# define FT_LONG_MAX 9223372036854775807L

typedef struct s_data
{	
	int rsvps;
	int hemlock_time;
	int	dinner_bell;
	int	drunken_stupor;
	int feasts;
	size_t symposium_start;
	size_t current_time;
}	t_data;

typedef struct s_plato
{
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t meal_lock;
	t_data	*data;
	int		id;
	int		meals_consumed;
	size_t	meal_time;
	bool	full;
	bool	hemlock;
}	t_plato;

/* ************************************************************************** */
/*									philo_toolkit							  */
/* ************************************************************************** */
long ft_atoi(char *str);
int	isdigit(int c);

/* ************************************************************************** */
/*									init									  */
/* ************************************************************************** */
int init_data(t_data *data, char **argv);
int init_plato(t_plato *plato, t_data *data);
//int init_threads(t_plato *plato, t_data *data);
int check_status(t_plato *plato, t_data *data);
int symp_routine(t_plato *plato, t_data *data);


/* ************************************************************************** */
/*									kronos									  */
/* ************************************************************************** */
size_t kronosophize(void);
size_t update_krono(size_t start_time);
void ft_usleep(size_t mili);

/* ************************************************************************** */
/*									mutex									  */
/* ************************************************************************** */
int destroy_fork_mutexes(t_plato* plato);
int clean_data(t_data *data);
int	init_mutexes(t_plato *plato, int rsvps);
void cleanup(t_plato *plato, t_data *data);

#endif
