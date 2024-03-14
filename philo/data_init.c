/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:54:41 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/13 23:20:49 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool ft_valid_argv(char *argv)
{
    int i;

    i = 0;    
    if (argv[i] == '+')
        i++;
    if (!ft_isdigit(argv[i]))
        return false;
    while (ft_isdigit(argv[i]) && argv[i] != '\0')
        i++;
    if (!ft_isdigit(argv[i]) && argv[i] != '\0')
        return false;
    if (!ft_isdigit(argv[i - 1]) && argv[i] == '\0')
	{
        return false;
	}
    return true;
}

bool check_overflow(char *argv)
{
    int i;

    i = 0;
    if (argv[i] == '+')
        i++;
    while (argv[i])
        i++;
    if (argv[0] == '+')
        i = i - 1;
    if (i > 10)
        return (false);
    return (true);
}

bool    check_argv(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (!ft_valid_argv(argv[i]) || !check_overflow(argv[i]))
            return (false);
        if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < 0)
            return (false);
        i++;
    }
    return (true);

}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_lead    *init_data(t_lead *leads, int argc,char **argv)
{
    if (check_argv(argc, argv))
    {
        leads->philos_num = ft_atoi(argv[1]);
        leads->time_to_die = ft_atoi(argv[2]);
        leads->time_to_eat = ft_atoi(argv[3]);
        leads->time_to_sleep = ft_atoi(argv[4]);
        leads->m_meals_allowed = -1;
        if (argc == 6)
            leads->m_meals_allowed = ft_atoi(argv[5]);
        leads->died = 0;
        leads->all_ate = 0;
        leads->time_init = get_time();
        
    }
    else
        error_exit(RED"Error: Invalid arguments\n"RST);
    return (leads);
}


