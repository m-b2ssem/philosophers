/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:41:24 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/10 02:18:22 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_rules *rules;
    if (argc == 5 || argc == 6)
    {
        rules = ft_malloc(sizeof(t_rules));
        rules = init_data(rules, argc, argv);
    }
    else
    {
        error_message(RED"Error: Invalid number of arguments\n"RST);
        return (1);
    }
}