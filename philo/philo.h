/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:13:02 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/16 01:05:08 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

/*
id: the id of the philo
last_meal: the time of the last meal
philo: the thread of the philo
*l_fork: the left fork of the philo
*r_fork: the right fork of the philo
reaper: the mutex for the reaper
times_ate: the number of times the philo ate
*rules: a pointer to the t_rules struct
*/
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	pthread_t		philo;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
	t_mutex			reaper;
	int				times_ate;
	struct s_lead	*leads;
}			t_philo;

/*num_philos;
time_init: time of the start of the program
ttd : time to die
tts: time to sleep
tte: time to eat
mma: max meals allowed
died: 1 if a philo died
all_ate: 1 if all philos ate
mess: mutex for printing
check: mutex for checking if a philo died
monitor: thread for checking if a philo died
*ph: a pointer to the t_philo struct
*/

typedef struct s_lead
{
	int				philos_num;
	long long		time_init;
	int				m_meals_allowed;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				died;
	int				all_ate;
	t_mutex			mess;
	t_mutex			checker;
	pthread_t		monitor;
	t_philo			*philo;
	int b;
}		t_lead;

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */

/* intilazing */
t_lead		*init_data(t_lead *rules, int argc, char **argv);
void		ft_message(char *messa, t_philo *ph);
int			one_philo(t_philo *ph);
int			check_philo_status_eating(t_philo *philo);
int			check_philo_status(t_philo *philo);

/* utils functions */
void		create_program(t_lead *leads);
void		error_message(char *message);
void		ft_mutex_lock_and_unlock(t_mutex *mutex, int check);
void		*ft_malloc(size_t bytes);
long long	get_time(void);
void		destroy_mutexes(t_lead *leads, t_mutex *forks);

/* check arguments */
bool		ft_valid_argv(char *argv);
bool		check_argv(int argc, char **argv);
bool		check_overflow(char *argv);

/*  monitor */
void		*ft_monitor(void *argv);
void		*start_simulation(void *argv);

/* libft functions*/
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

#endif
