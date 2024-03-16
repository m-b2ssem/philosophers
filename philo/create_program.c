/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:52:09 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/16 01:04:51 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_threads(t_lead *leads)
{
	int	i;

	leads->b = leads->philos_num;
	i = 0;
	// lock die
	pthread_mutex_lock(&leads->checker);
	while (i < leads->philos_num)
	{
		// if(i == 5)
		// {
		// 	leads->died = 1;
		// 	leads->philos_num = i;
		// 	error_message(RED"error with creating the thread"RST);
		// 	break;
		// }
		if (pthread_create(&leads->philo[i].philo, NULL,
				&start_simulation, &leads->philo[i]) != 0)
		{
			error_message(RED"error with creating the thread"RST);
			// leads->num = i;
			leads->philos_num = i;
			// die = 1
			leads->died = 1;
			break;
		}
		//usleep(100);
		i++;
	}
	// unlock die
	if (leads->b == leads->philos_num)
	{
		if (pthread_create(&leads->monitor, NULL, &ft_monitor, leads) != 0)
		{
			error_message(RED"error with creating the thread nnnnnnn"RST);
			leads->philos_num = i;
			// die = 1
			leads->died = 1;
			leads->b = -1;
		}
	}
	pthread_mutex_unlock(&leads->checker);
}

static	void	join_threads(t_lead *leads, t_mutex *forks)
{
	int	i;

	i = 0;
	if (leads->b == leads->philos_num)
	{
		if (pthread_join(leads->monitor, NULL) != 0)
		{
			error_message(RED"couldn't join the thread"RST);
		}
	}
	while (i < leads->philos_num)
	{
		if (pthread_join(leads->philo[i].philo, NULL) != 0)
		{
			error_message(RED"couldn't join the thread11"RST);
			break;
		}
		i++;
	}
	destroy_mutexes(leads, forks);
}

static	t_philo	*init_philos(t_lead *leads, t_mutex *forks)
{
	int	i;

	i = 0;
	while (i < leads->philos_num)
	{
		leads->philo[i].id = i + 1;
		leads->philo[i].last_meal = get_time();
		leads->philo[i].times_ate = 0;
		leads->philo[i].r_fork = &forks[i];
		leads->philo[i].l_fork = &forks[(i + 1) % leads->philos_num];
		leads->philo[i].leads = leads;
		if (pthread_mutex_init(&leads->philo[i].reaper, NULL) != 0)
			error_message("failed to init mutex!\n");
		i++;
	}
	return (leads->philo);
}

static	int	init_forks(t_lead *leads, t_mutex *forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&leads->checker, NULL) != 0)
	{
		error_message(RED"error with init mutex"RST);
		return(1);
	}
	if (pthread_mutex_init(&leads->mess, NULL) != 0)
	{
		pthread_mutex_destroy(&leads->checker);
		error_message(RED"error with init mutex"RST);
		return (1);
	}
	while (i < leads->philos_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&leads->checker);
			pthread_mutex_destroy(&leads->mess);
			while (i > 0 )
			{
				pthread_mutex_destroy(&forks[i--]);
			}
			
			return (error_message(RED"error with init mutex"RST), 1);
		}
		i++;
	}
	return (0);
}

void	create_program(t_lead *leads)
{
	t_mutex	*forks;

	forks = malloc(sizeof(t_mutex) * leads->philos_num);
	if (!forks)
		return ;
	leads->philo = malloc(sizeof(t_philo) * leads->philos_num);
	if (!leads->philo)
		return (free(forks));
	if (init_forks(leads, forks) == 1)
	{
		free(forks);
		free(leads->philo);
		error_message(RED"no forks was init"RST);
		return ;
	}
	leads->philo = init_philos(leads, forks);
	if (leads->philo == 0)
		error_message(RED"no philosophrs was init"RST);
	init_threads(leads);
	join_threads(leads, forks);
	free(forks);
	free(leads->philo);
	return ;
}
