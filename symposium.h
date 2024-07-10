/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:17:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/10 18:28:17 by jbremser         ###   ########.fr       */
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

typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
	EXIT_INVALID_ARGS = 201,
	EXIT_INIT_ERROR = 202,
	EXIT_MALLOC_FAIL = 203,
	EXIT_MUTEX_INIT_ERROR = 204
}	t_error;

typedef struct s_plato
{
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t meal_lock;
	struct	s_moniter		*alcibiades;
	int				id;
	int				meals_consumed;
	size_t			meal_time;
	bool			full;
	bool			hemlock;
}	t_plato;

typedef struct s_moniter
{	
	int rsvps;
	int hemlock_time;
	int	dinner_bell;
	int	drunken_stupor;
	int feasts;
	int full_philos;
	t_plato	*plato;
	size_t symposium_start;
	size_t current_time;
	pthread_mutex_t lock_print;
}	t_moniter;

/* ************************************************************************** */
/*									philo_toolkit							  */
/* ************************************************************************** */
long ft_atol(char *str);
void print_structs(t_moniter *data, t_plato *plato);
int check_args(char **argv, t_moniter *alcibiades);


/* ************************************************************************** */
/*									init									  */
/* ************************************************************************** */
int init_moniter(t_moniter *data, char **argv);
int init_plato(t_plato *plato, t_moniter *data);
//int init_threads(t_plato *plato, t_moniter *data);
int check_status(t_plato *plato, t_moniter *data);
int symp_routine(t_plato *plato, t_moniter *data);


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
int clean_data(t_moniter *data);
int	init_mutexes(t_plato *plato, int rsvps);
void cleanup(t_plato *plato, t_moniter *data);

#endif
