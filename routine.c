#include "philo.h"

void *philo_routine(void *args)
{
  t_philo *philo;
  philo = (t_philo *)args;

  if(philo->id % 2 == 0)
    ft_usleep(1);
  while(!dead_loop(philo))
  {
    eating(philo);
    sleeping(philo);
    thinking(philo);
  }
  return(NULL);
}