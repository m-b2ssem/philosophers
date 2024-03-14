/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:18 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/14 00:47:01 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philos_died(t_lead *rules)
{
	int	i;

	i = 0;
	while (i < rules->philos_num)
	{
		ft_mutex_lock_and_unlock(&rules->philo[i].reaper, 'l');
		if ((get_time() - rules->philo[i].last_meal) > rules->time_to_die)
		{
			ft_message("died\n", &rules->philo[i]);
            ft_mutex_lock_and_unlock(&rules->checker, 'l');
			rules->died = 1;
			ft_mutex_lock_and_unlock(&rules->checker, 'u');
			ft_mutex_lock_and_unlock(&rules->philo[i].reaper, 'u');
			return (1);
		}
		ft_mutex_lock_and_unlock(&rules->philo[i].reaper, 'u');
		i++;
	}
	return (0);
}

static int	philos_ate(t_lead *rules)
{
	if (rules->m_meals_allowed == -1)
		return (0);
	ft_mutex_lock_and_unlock(&rules->checker, 'l');
	if (rules->all_ate == rules->philos_num)
	{
		ft_mutex_lock_and_unlock(&rules->checker, 'u');
		return (1);
	}
	ft_mutex_lock_and_unlock(&rules->checker, 'u');
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_lead	*rules;

	rules = (t_lead *)arg;
	while (1)
	{
		if (philos_died(rules))
			return (NULL);
		if (philos_ate(rules))
			return (NULL);
	}
}

