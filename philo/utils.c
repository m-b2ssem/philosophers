/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:41:09 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/16 15:30:17 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		write(1, &message[i], 1);
		i++;
	}
	return ;
}

int	init_checker_mess(t_lead *leads)
{
	if (pthread_mutex_init(&leads->checker, NULL) != 0)
	{
		error_message(RED"error with init mutex"RST);
		return (1);
	}
	if (pthread_mutex_init(&leads->mess, NULL) != 0)
	{
		pthread_mutex_destroy(&leads->checker);
		error_message(RED"error with init mutex"RST);
		return (1);
	}
	return (0);
}

void	ft_mutex_lock_and_unlock(t_mutex *mutex, int check)
{
	if (check == 'l')
	{
		if (pthread_mutex_lock(mutex) != 0)
			error_message("error with locking mutex\n");
	}
	if (check == 'u')
	{
		if (pthread_mutex_unlock(mutex) != 0)
			error_message("error with unlocking mutex\n");
	}
}

void	destroy_mutexes(t_lead *leads, t_mutex *forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&leads->checker) != 0)
		error_message(RED"couldn't destroy message"RST);
	while (i < leads->philos_num)
	{
		if (pthread_mutex_destroy(&leads->philo[i].reaper) != 0)
			error_message(RED"couldn't destroy reaper"RST);
		if (pthread_mutex_destroy(&forks[i]) != 0)
			error_message(RED"couldn't destroy the forks"RST);
		i++;
	}
}
