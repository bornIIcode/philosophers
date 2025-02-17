#include "philo.h"

void	*dead_monitor(void *pointer)
{
	t_program *prog;

	prog = (t_program *)pointer;
	while (1)
		if (check_if_dead(prog) == 1 || all_eat(prog) == 1)
			break ;
	return (pointer);
}
