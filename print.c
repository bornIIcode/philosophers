/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:25:20 by ytabia            #+#    #+#             */
/*   Updated: 2025/02/25 11:31:03 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int flag, char *str)
{
	if (flag == 1)
	{
		write(2, str, ft_strlen(str));
		exit(1);
	}
}

void	print_msg(t_philo *philo, int id, char *str)
{
	size_t	time;

	if (dead_loop(philo))
		return ;
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}
