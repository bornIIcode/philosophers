/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:02:32 by ytabia            #+#    #+#             */
/*   Updated: 2025/02/25 11:02:33 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_threads(t_program *prog)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, dead_monitor, prog) != 0)
		return (-1);
	while (i < prog->num_of_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, philo_routine,
				&prog->philos[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < prog->num_of_philos)
	{
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (-1);
	return (0);
}
