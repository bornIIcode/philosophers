#include "philo.h"

void thinking(t_philo *philo)
{
  print_msg(philo, philo->id, "is thinking\n");
}


void sleeping(t_philo *philo)
{
  print_msg(philo, philo->id, "is sleeping\n");
  ft_usleep(philo->prog->time_to_sleep);
}

// void eating(t_philo *philo)
// {
//   t_program *prog;
//   prog = philo->prog;
//   pthread_mutex_lock(philo->r_fork);
//   print_msg(philo, philo->id, "is taken a fork\n");
//   if(prog->num_of_philos == 1)
//   {
//     ft_usleep(prog->time_to_die);
//     pthread_mutex_unlock(philo->r_fork);
//     return;
//   }
//   pthread_mutex_lock(philo->l_fork);
//   print_msg(philo, philo->id, "is taken a fork\n");
//   philo->eating = 1;
//   print_msg(philo, philo->id, "is eating\n");
//   pthread_mutex_lock(philo->meal_lock);
//   philo->last_meal = get_time();
//   philo->meals_eaten++;
//   ft_usleep(prog->time_to_eat);
//   philo->eating = 0;
//   pthread_mutex_unlock(philo->meal_lock);
//   pthread_mutex_unlock(philo->l_fork);
//   pthread_mutex_unlock(philo->r_fork);
// }

void eating(t_philo *philo)
{
    t_program *prog;
    prog = philo->prog;

    pthread_mutex_lock(philo->r_fork);
    print_msg(philo, philo->id, "is taken a fork\n");
    if(prog->num_of_philos == 1)
    {
        ft_usleep(prog->time_to_die);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
    pthread_mutex_lock(philo->l_fork);
    print_msg(philo, philo->id, "is taken a fork\n");

    pthread_mutex_lock(philo->meal_lock);
    philo->eating = 1;
    philo->last_meal = get_time();  // Update last_meal before printing
    pthread_mutex_unlock(philo->meal_lock);

    print_msg(philo, philo->id, "is eating\n");
    ft_usleep(prog->time_to_eat);

    pthread_mutex_lock(philo->meal_lock);
    philo->meals_eaten++;
    philo->eating = 0;
    pthread_mutex_unlock(philo->meal_lock);

    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}