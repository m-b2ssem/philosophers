/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:54:41 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/10 02:13:29 by bmahdi           ###   ########.fr       */
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

static long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_rules    *init_data(t_rules *rules, int argc,char **argv)
{
    if (check_argv(argc, argv))
    {
        rules->num_philos = ft_atoi(argv[1]);
        rules->time_init = get_time();
        rules->ttd = ft_atoi(argv[2]);
        rules->tte = ft_atoi(argv[3]);
        rules->tts = ft_atoi(argv[4]);
        if (argc == 6)
            rules->mma = ft_atoi(argv[5]);
        else
            rules->mma = -1;
        rules->died = 0;
        rules->all_ate = 0;
        
    }
    else
        error_message(RED"Error: Invalid arguments\n"RST);
    return (rules);
}


