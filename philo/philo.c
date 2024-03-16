/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahdi <bmahdi@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:41:24 by bmahdi            #+#    #+#             */
/*   Updated: 2024/03/16 15:15:28 by bmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_lead	*leads;

	if (argc == 5 || argc == 6)
	{
		leads = malloc(sizeof(t_lead));
		if (!leads)
			return (error_message(RED"error with init mutex"RST), 1);
		leads = init_data(leads, argc, argv);
		if (!leads)
			return (error_message(RED"argument are not valid"RST), 1);
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
