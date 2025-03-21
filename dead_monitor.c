/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:02:42 by ytabia            #+#    #+#             */
/*   Updated: 2025/02/25 11:26:56 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_monitor(void *args)
{
	t_program	*prog;

	prog = (t_program *)args;
	while (1)
	{
		if (check_if_dead(prog) == 1 || all_eat(prog) == 1)
			break ;
		usleep(100);
	}
	return (args);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	check_if_dead(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		if (philo_dead(&prog->philos[i], prog->time_to_die))
		{
			print_msg(&prog->philos[i], prog->philos[i].id, "died\n");
			pthread_mutex_lock(prog->philos[i].dead_lock);
			*prog->philos[i].dead = 1;
			pthread_mutex_unlock(prog->philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	size_t	last_meal_time;
	int		eating_status;

	pthread_mutex_lock(philo->meal_lock);
	last_meal_time = philo->last_meal;
	eating_status = philo->eating;
	pthread_mutex_unlock(philo->meal_lock);
	if (get_time() - last_meal_time >= time_to_die + 1 && eating_status == 0)
		return (1);
	return (0);
}

int	all_eat(t_program *prog)
{
	int	i;
	int	all_eat;

	if (prog->num_times_to_eat <= 0)
		return (0);
	i = 0;
	all_eat = prog->num_of_philos;
	pthread_mutex_lock(prog->philos[0].meal_lock);
	while (i < prog->num_of_philos)
	{
		if (prog->philos[i].meals_eaten < prog->num_times_to_eat)
			all_eat--;
		i++;
	}
	pthread_mutex_unlock(prog->philos[0].meal_lock);
	if (all_eat == 0)
		return (0);
	return (1);
}
