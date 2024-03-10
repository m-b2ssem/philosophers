#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

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

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	reaper;
	int				times_ate;
	struct s_rules	*rules;
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

typedef struct s_rules
{
	int				num_philos;
	int     		time_init;
	int				ttd;
	int				tts;
	int				tte;
	int				mma;
	int				died;
	int				all_ate;
	pthread_mutex_t	mess;
	pthread_mutex_t	check;
	pthread_t		monitor;
	t_philo			*ph;
}				t_rules;

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */

/* utils functions */
t_rules    *init_data(t_rules *rules, int argc,char **argv);
void    error_message(char *message);
void	mutex_lock_and_unlock(pthread_mutex_t *mutex, int check);
void	*ft_malloc(size_t bytes);

/* check arguments */
bool    ft_valid_argv(char *argv);
bool    check_argv(int argc, char **argv);
bool    check_overflow(char *argv);


/* libft functions*/
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif