#include "philo.h"

void *dead_monitor(void *args)
{
    t_program *prog;

    prog = (t_program *)args;
    while (1)
    {
        if (check_if_dead(prog) == 1 || all_eat(prog) == 1)
            break;
        usleep(100);  // Add a small sleep to prevent excessive CPU usage
    }
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

int philo_dead(t_philo *philo, size_t time_to_die)
{
    size_t last_meal_time;
    int eating_status;

    pthread_mutex_lock(philo->meal_lock);
    last_meal_time = philo->last_meal;
    eating_status = philo->eating;
    pthread_mutex_unlock(philo->meal_lock);

    if (get_time() - last_meal_time >= time_to_die + 1 && eating_status == 0)
        return (1);
    return (0);
}

