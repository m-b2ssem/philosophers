/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:43:07 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/13 01:42:05 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	join_threads(t_lead *leads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (pthread_join(leads->monitor, NULL) != 0)
		error_message("Couldn't join thread1!\n");
	while (i < leads->philos_num)
	{
		if (pthread_join(leads->philo[i].philo, NULL) != 0)
			error_message("Couldn't join thread2!\n");
		i++;
	}
	i = 0;
	while (i < leads->philos_num)
	{
		pthread_mutex_destroy(&leads->philo[i].reaper);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&leads->mess);
}

void	create_threads(t_lead *leads)
{
	int	i;

	i = 0;
	while (i < leads->philos_num)
	{
		if (pthread_create(&leads->philo[i].philo, NULL, &start_simulation, &leads->philo[i]) != 0)
			error_message("Couldn't create thread!\n");
		usleep(100);
		i++;
	}
	if (pthread_create(&leads->monitor, NULL, &ft_monitor, leads) != 0)
		error_message("Couldn't create thread!\n");
}

void    init_threads(t_lead *rules, t_mutex *forks)
{
    create_threads(rules);
    join_threads(rules, forks);
}

/*

