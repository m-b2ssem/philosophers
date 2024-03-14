/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:41:24 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/14 22:03:37 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_lead	*leads;

	if (argc == 5 || argc == 6)
	{
		leads = ft_malloc(sizeof(t_lead));
		leads = init_data(leads, argc, argv);
		create_program(leads);
		free(leads);
	}
	else
	{
		error_message(RED"Error: Invalid number of arguments\n"RST);
		return (1);
	}
	return (0);
}
