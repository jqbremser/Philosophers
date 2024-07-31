/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:17:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/26 14:24:25 by jbremser         ###   ########.fr       */
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

# define RFORK	"has taken a right fork"
# define LFORK	"has taken a left fork"

# define EATING		"is gorging"
# define SLEEPING	"is drinking"
# define THINKING	"is pontificating"
# define DIED		"has taken hemlock"
# define SOCRATES	"\nIf you think that by killing men you can prevent\nsome one from censuring your evil lives, you are mistaken;\nthat is not a way of escape which is either possible or honourable;\nthe easiest and the noblest way is not to be disabling others,\nbut to be improving yourselves.\n\n-Socrates\n\n"


typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
	EXIT_INVALID_ARGS = 201,
	EXIT_INIT_ERROR = 202,
	EXIT_MALLOC_FAIL = 203,
	EXIT_MUTEX_INIT_ERROR = 204,
	EXIT_THREADS_ERROR = 205,
	EXIT_PHILO_ERROR = 206,
	EXIT_AL_ERROR = 207
}	t_error;

typedef struct s_philo
{
	int					id;
	struct	s_moniter	*overseer;
	size_t					hemlock_time;
	size_t					dinner_bell;
	int					drunken_stupor;
	int					feasts;
	size_t				*symposium_start;
	size_t				current_time;
	pthread_t			thread;
	int					meals_consumed;
	size_t				meal_time;
	bool				full;
	bool				*hemlock_taken;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		meal_lock;
}	t_philo;

typedef struct s_moniter
{	
	size_t			symposium_start;
	int				rsvps;
	int				full_philos;
	bool			all_fed;
	bool			hemlock_taken;
	pthread_mutex_t	symposium_lock;
	pthread_mutex_t	hemlock;
	pthread_mutex_t	print_lock;
	t_philo			*philo;
}	t_moniter;

/* ************************************************************************** */
/*									philo_toolkit							  */
/* ************************************************************************** */
long ft_atol(char *str);
void print_structs(t_philo *philo);
int check_args(char **argv);


/* ************************************************************************** */
/*									init									  */
/* ************************************************************************** */
int init_moniter(t_moniter *overseer, char **argv);
int init_philo(t_moniter *overseer, char **argv);


/* ************************************************************************** */
/*									kronos									  */
/* ************************************************************************** */
size_t kronosophize(void);
size_t update_krono(size_t start_time);
void ft_usleep(size_t mili, t_moniter *overseer);

/* ************************************************************************** */
/*									mutex									  */
/* ************************************************************************** */
int destroy_fork_mutexes(t_philo* philo);
int clean_data(t_moniter *data);
int	init_mutexes(t_philo *philo);
void cleanup(t_philo *philo, t_moniter *data);

/* ************************************************************************** */
/*									routine									  */
/* ************************************************************************** */
void *symp_routine(void *ptr);
void *death_routine(void *ptr);
int hemlocked(t_moniter *overseer);
int is_full(t_moniter *al);
void ostracize(t_moniter *al);

/* ************************************************************************** */
/*									locks									  */
/* ************************************************************************** */
int print_message(const char *message, t_philo *philo);
int is_alive(t_philo *philo);

#endif
