/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:17:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/04 02:28:28 by jbremser         ###   ########.fr       */
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

# define RFORK	"has taken a fork"
# define LFORK	"has taken a fork"

# define EATING		"is gorging"
# define SLEEPING	"is drinking"
# define THINKING	"pontificates"
# define DIED		"has taken hemlock"

typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
	EXIT_INVALID_ARGS = 201,
	EXIT_MON_ERROR = 202,
	EXIT_MALLOC_FAIL = 203,
	EXIT_MUTEX_INIT_ERROR = 204,
	EXIT_THREADS_ERROR = 205,
	EXIT_PHILO_ERROR = 206,
	EXIT_TR_ERROR = 207
}	t_error;

typedef struct s_philo
{
	struct s_monitor	*overseer;
	size_t				*symposium_start;
	size_t				meal_time;
	bool				*hemlock_taken;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					feasts;
	int					id;
	pthread_t			thread;
	int					meals_consumed;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		meal_lock;
}	t_philo;

typedef struct s_monitor
{	
	t_philo			*philo;
	int				full_philos;
	int				rsvps;
	bool			hemlock_taken;
	size_t			symposium_start;
	pthread_mutex_t	symposium_lock;
	pthread_mutex_t	hemlock;
	pthread_mutex_t	print_lock;
}	t_monitor;

/* ************************************************************************** */
/*									the_help								  */
/* ************************************************************************** */
int		check_args(char **argv);
long	ft_atol(char *str);
void	unlock_forks(t_philo *philo);
/* ************************************************************************** */
/*									init									  */
/* ************************************************************************** */
int		init_monitor(t_monitor *overseer, char **argv);
int		init_philo(t_monitor *overseer, char **argv);
/* ************************************************************************** */
/*									kronos									  */
/* ************************************************************************** */
size_t	update_time(void);
void	ft_usleep(size_t mili, t_monitor *overseer);
/* ************************************************************************** */
/*									threads									  */
/* ************************************************************************** */
int		init_threads_routine(t_monitor *overseer);
/* ************************************************************************** */
/*									routine									  */
/* ************************************************************************** */
void	*symp_routine(void *ptr);
/* ************************************************************************** */
/*									locks									  */
/* ************************************************************************** */
int		print_message(const char *message, t_philo *philo);
void	ostracize(t_monitor *overseer);
int		hemlocked(t_monitor *overseer);
int load_philosopher_names(const char *filename, char **philosopher_names, int max_philosophers);

#endif
