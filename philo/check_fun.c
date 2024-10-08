/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:00:19 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/16 15:30:46 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_status_eating(t_philo *philo)
{
	ft_mutex_lock_and_unlock(&philo->leads->checker, 'l');
	if (philo->leads->died == 1
		|| philo->leads->all_ate == philo->leads->philos_num)
	{
		ft_mutex_lock_and_unlock(&philo->leads->checker, 'u');
		ft_mutex_lock_and_unlock(philo->l_fork, 'u');
		ft_mutex_lock_and_unlock(philo->r_fork, 'u');
		return (1);
	}
	ft_mutex_lock_and_unlock(&philo->leads->checker, 'u');
	return (0);
}

int	check_philo_status(t_philo *philo)
{
	ft_mutex_lock_and_unlock(&philo->leads->checker, 'l');
	if (philo->leads->died == 1
		|| philo->leads->all_ate == philo->leads->philos_num)
	{
		ft_mutex_lock_and_unlock(&philo->leads->checker, 'u');
		return (1);
	}
	ft_mutex_lock_and_unlock(&philo->leads->checker, 'u');
	return (0);
}

int	one_philo(t_philo *ph)
{
	if (ph->leads->philos_num == 1)
	{
		ft_mutex_lock_and_unlock(ph->l_fork, 'l');
		ft_message("has taken a fork\n", ph);
		ft_mutex_lock_and_unlock(ph->l_fork, 'u');
		return (1);
	}
	return (0);
}

void	ft_message(char *messa, t_philo *ph)
{
	long long	time;

	time = get_time() - ph->leads->time_init;
	pthread_mutex_lock(&ph->leads->checker);
	if (ph->leads->died || ph->leads->all_ate == ph->leads->philos_num)
	{
		pthread_mutex_unlock(&ph->leads->checker);
		return ;
	}
	pthread_mutex_lock(&ph->leads->mess);
	printf("%lld %d %s", time, ph->id, messa);
	pthread_mutex_unlock(&ph->leads->mess);
	pthread_mutex_unlock(&ph->leads->checker);
	return ;
}

void	init_monitor(t_lead *leads, int i)
{
	if (pthread_create(&leads->monitor, NULL, &ft_monitor, leads) != 0)
	{
		error_message(RED"error with creating the thread"RST);
		leads->philos_num = i;
		leads->died = 1;
		leads->b = -1;
	}
}
