/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:18 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/13 01:35:22 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_monitor(void *argv)
{
	t_lead	*leads;

	leads = (t_lead *)argv;
	while (1)
	{
		if (philos_died(leads))
			return (NULL);
		if (philos_ate(leads))
			return (NULL);
	}
}

int	philos_died(t_lead *leads)
{
	int	i;

	i = 0;
	while (i < leads->philos_num)
	{
        mutex_lock_and_unlock(&leads->philo[i].reaper, 'l');
		if ((get_time() - leads->philo[i].last_meal) > leads->time_to_die)
		{
			print_message("died\n", &leads->philo[i]);
            mutex_lock_and_unlock(&leads->checker, 'l');
			leads->died = 1;
            mutex_lock_and_unlock(&leads->checker, 'u');
            mutex_lock_and_unlock(&leads->philo[i].reaper, 'u');
			return (1);
		}
        mutex_lock_and_unlock(&leads->philo[i].reaper, 'u');
		i++;
	}
	return (0);
}

int	philos_ate(t_lead *leads)
{
	if (leads->m_meals_allowed == -1)
		return (0);
	mutex_lock_and_unlock(&leads->checker, 'l');
	if (leads->all_ate == leads->philos_num)
	{
		mutex_lock_and_unlock(&leads->checker, 'u');
		return (1);
	}
	mutex_lock_and_unlock(&leads->checker, 'u');
	return (0);
}

