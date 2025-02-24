#include "philo.h"

void	*philo_routine(void *args)
{
	t_philo		*philo;
	t_program	*prog;

	philo = (t_philo *)args;
	prog = philo->prog;
	if (prog->num_of_philos == 1)
	{
		print_msg(philo, philo->id, "has taken a fork\n");
		ft_usleep(prog->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		// ft_usleep(5);
		if (philo->meals_eaten == prog->num_times_to_eat)
			break ;
	}
	return (NULL);
}
