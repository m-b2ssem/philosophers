/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:18 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/11 15:45:47 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_monitor(void *argv)
{
    (void)argv;
    printf("done");
    return NULL;
}

void    *simulter(void *argv)
{
    (void)argv;
    while (1)
    {
        printf("done1");
    }
    return NULL;
}
