#include "philo.h"

int creat_threads(t_program *prog)
{
  // t_philo *philo;
  int i;
  // size_t start_time;
  pthread_t monitor;

  i = 0;
  while(i < prog->num_of_philos)
  {
    prog->philos[i].prog = prog;
    pthread_create(&prog->philos[i].thread, NULL, philo_routine, &prog->philos[i]);
    i++;
  }
  pthread_create(&monitor, NULL, dead_monitor, prog);
  i = 0;
  while(i < prog->num_of_philos)
  {
    pthread_join(prog->philos[i].thread, NULL);
    i++;
  }
  pthread_join(monitor, NULL);
  // printf("num of philos -->%d\n", prog->num_of_philos);
  return(0);
}


int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// Check if any philo died

int	check_if_dead(t_program *prog)
{
	int	i;
	i = 0;
	while (i < prog->num_of_philos)
	{
		if (philosopher_dead(&prog->philos[i], prog->time_to_die))
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
