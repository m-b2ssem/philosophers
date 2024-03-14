/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:00:19 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/14 00:48:44 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_philo_status_eating(t_philo *philo)
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

int check_philo_status(t_philo *philo)
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


int    one_philo(t_philo *ph)
{
    ft_mutex_lock_and_unlock(ph->l_fork, 'l');
    ft_message("has taken a fork\n", ph);
    ft_mutex_lock_and_unlock(ph->l_fork, 'u');
    return (1);
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
	pthread_mutex_unlock(&ph->leads->checker);
	if (pthread_mutex_lock(&ph->leads->mess) != 0)
		error_message("Failed locking print mutex\n");
	printf("%lld %d %s", time, ph->id, messa);
	if (pthread_mutex_unlock(&ph->leads->mess) != 0)
		return ;
}