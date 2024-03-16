/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:18 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/16 02:23:32 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_died(t_lead *leads)
{
	int	i;
	long long time;

	i = 0;
	time = get_time() - leads->time_init;
	while (i < leads->philos_num)
	{
		ft_mutex_lock_and_unlock(&leads->philo[i].reaper, 'l');
		if ((get_time() - leads->philo[i].last_meal) > leads->time_to_die)
		{
			//ft_message("died", &leads->philo[i]);
			pthread_mutex_lock(&leads->checker);
			leads->died = 1;
			//printf("%d\n", leads->philo->id);
			printf("%lld %d %s\n", time, leads->philo[i].id, "died");
			pthread_mutex_unlock(&leads->checker);
			ft_mutex_lock_and_unlock(&leads->philo[i].reaper, 'u');
			return (1);
		}
		ft_mutex_lock_and_unlock(&leads->philo[i].reaper, 'u');
		i++;
	}
	return (0);
}

static int	ft_ate(t_lead *leads)
{
	if (leads->m_meals_allowed == -1)
		return (0);
	ft_mutex_lock_and_unlock(&leads->checker, 'l');
	if (leads->all_ate == leads->philos_num)
	{
		leads->died = 1;
		ft_mutex_lock_and_unlock(&leads->checker, 'u');
		return (1);
	}
	ft_mutex_lock_and_unlock(&leads->checker, 'u');
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_lead	*leads;

	leads = (t_lead *)arg;
	while (1)
	{
		//usleep(100);
		if (ft_died(leads))
			return (NULL);
		if (ft_ate(leads))
			return (NULL);
	}
}
