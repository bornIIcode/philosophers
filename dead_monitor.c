#include "philo.h"

void	*dead_monitor(void *args)
{
	t_program *prog;

	prog = (t_program *)args;
	while (1)
		if (check_if_dead(prog) == 1 || all_eat(prog) == 1)
			break ;
	return (args);
}

int dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if(*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return(1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return(0);
}

int	check_if_dead(t_program *prog)
{
	int	i;
	i = 0;
	while (i < prog->num_of_philos)
	{
		if (philo_dead(&prog->philos[i], prog->time_to_die))
		{
			print_msg(&prog->philos[i], prog->philos[i].id, "is died\n");
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
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die && philo->eating == 0)
  	{
    	pthread_mutex_unlock(philo->meal_lock);
		return (1);
  	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

