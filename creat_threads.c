#include "philo.h"

int	creat_threads(t_program *prog)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	pthread_create(&monitor, NULL, dead_monitor, prog);
	while (i < prog->num_of_philos)
	{
		pthread_create(&prog->philos[i].thread, NULL, philo_routine,
			&prog->philos[i]);
		i++;
	}
	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
