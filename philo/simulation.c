/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:32:26 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/13 01:36:16 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
    if (check_philo_status(philo))
    {
        return (1);
    }
	philo->last_meal = get_time();
	print_message("is eating\n", philo);
	mutex_lock_and_unlock(&philo->leads->checker, 'l');
	philo->times_ate++;
	if (philo->leads->m_meals_allowed != -1 && philo->times_ate == philo->leads->m_meals_allowed)
		philo->leads->all_ate++;
	mutex_lock_and_unlock(&philo->leads->checker, 'u');
	mutex_lock_and_unlock(&philo->reaper, 'u');
	usleep(philo->leads->time_to_eat * 1000);
	mutex_lock_and_unlock(philo->l_fork, 'u');
	mutex_lock_and_unlock(philo->r_fork, 'u');
	return (0);
}

int	thinking(t_philo *philo)
{
    if (check_philo_status(philo))
    {
        return (1);
    }
	mutex_lock_and_unlock(&philo->leads->m_meals_allowed, 'u');
	ft_message("is thinking\n", philo);
	return (0);
}

int	sleeping(t_philo *philo)
{
    if (check_philo_status(philo))
    {
        return (1);
    }
	ft_message("is sleeping\n", philo);
	usleep(philo->leads->time_to_sleep * 1000);
	return (0);
}

int	take_forks(t_philo *philo)
{
    if (check_philo_status(philo))
    {
        return (1);
    }
	if (philo->id % 2)
	{
		mutex_lock_and_unlock(philo->l_fork, 'l');
		ft_message("has taken a fork\n", philo);
		mutex_lock_and_unlock(philo->r_fork, 'l');
		ft_message("has taken a fork\n", philo);
	}
	else
	{
		mutex_lock_and_unlock(philo->r_fork, 'l');
		ft_message("has taken a fork\n", philo);
		mutex_lock_and_unlock(philo->l_fork, 'l');
		ft_message("has taken a fork\n", philo);
	}
	return (0);
}

void    *start_simulation(void *argv)
{
    t_philo *ph;

    ph = (t_philo *)argv;
    if (ph->leads->philos_num == 1)
        if (one_philo(ph))
            return (NULL);
    while (1)
	{
		if (take_forks(ph))
			return (NULL);
		if (eating(ph))
			return (NULL);
		if (sleeping(ph))
			return (NULL);
		if (thinking(ph))
			return (NULL);
	}
    return (NULL);
}