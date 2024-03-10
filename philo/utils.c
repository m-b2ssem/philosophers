/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:41:09 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/10 18:57:38 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_message(char *message)
{
    int i;

    i = 0;
    while (message[i])
    {
        write(2, &message[i], 1);
        i++;
    }
    return ;
}

void    error_exit(char *message)
{
    int i;

    i = 0;
    while (message[i])
    {
        write(2, &message[i], 1);
        i++;
    }
    exit(1);
}

void	*ft_malloc(size_t bytes)
{
	void	*mal;

	mal = malloc(bytes);
	if (mal == NULL)
		error_message("Error with the malloc");
	return (mal);
}

void	mutex_lock_and_unlock(pthread_mutex_t *mutex, int check)
{
	if (check == 'l')
	{
		if (pthread_mutex_lock(mutex) != 0)
			error_message("error with locking mutex\n");
	}
	if (check == 'u')
	{
		if (pthread_mutex_unlock(mutex) != 0)
			error_message("error with unlocking mutex\n");
	}
}
    