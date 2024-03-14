/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:32:26 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/14 00:45:13 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleeping(t_philo *philo)
{
	if (check_philo_status(philo))
		return(1);
	ft_message("is sleeping\n", philo);
	usleep(philo->leads->time_to_sleep * 1000);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (check_philo_status(philo))
		return(1);
	ft_message("is thinking\n", philo);
	return (0);
}

static int	eating(t_philo *philo)
{
	if (check_philo_status_eating(philo))
		return(1);
	ft_mutex_lock_and_unlock(&philo->reaper, 'l');
	philo->last_meal = get_time();
	ft_message("is eating\n", philo);
	ft_mutex_lock_and_unlock(&philo->leads->checker, 'l');
	philo->times_ate++;
	if (philo->leads->m_meals_allowed != -1 && philo->times_ate == philo->leads->m_meals_allowed)
		philo->leads->all_ate++;
	ft_mutex_lock_and_unlock(&philo->leads->checker, 'u');
	ft_mutex_lock_and_unlock(&philo->reaper, 'u');
	usleep(philo->leads->time_to_eat * 1000);
	ft_mutex_lock_and_unlock(philo->l_fork, 'u');
	ft_mutex_lock_and_unlock(philo->r_fork, 'u');
	return (0);
}

static int	take_forks(t_philo *philo)
{
	if (check_philo_status(philo))
		return(1);
	if (philo->id % 2)
	{
		ft_mutex_lock_and_unlock(philo->l_fork, 'l');
		ft_message("has taken a fork\n", philo);
		ft_mutex_lock_and_unlock(philo->r_fork, 'l');
		ft_message("has taken a fork\n", philo);
	}
	else
	{
		ft_mutex_lock_and_unlock(philo->r_fork, 'l');
		ft_message("has taken a fork\n", philo);
		ft_mutex_lock_and_unlock(philo->l_fork, 'l');
		ft_message("has taken a fork\n", philo);
	}
	return (0);
}

void	*start_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->leads->philos_num == 1)
		if (one_philo(philo))
			return (NULL);
	while (1)
	{
		if (take_forks(philo))
			return (NULL);
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}