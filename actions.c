#include "philo.h"

void thinking(t_philo *philo)
{
  print_msg(philo, philo->id, "is thinking\n");
}


// void sleeping(t_philo *philo)
// {
//   print_msg(philo, philo->id, "is sleeping\n");
//   ft_usleep(philo->prog->time_to_sleep);
// }

void sleeping(t_philo *philo)
{
    size_t sleep_start;
    print_msg(philo, philo->id, "is sleeping\n");
    sleep_start = get_time();
    while(!dead_loop(philo))
    {
        if(get_time() - sleep_start >= (size_t)philo->prog->time_to_sleep)
            break;
        usleep(1000);  // Sleep in 1ms intervals
    }
}

void eating(t_philo *philo)
{
    t_program *prog;
    size_t eat_start;

    prog = philo->prog;
    eat_start = get_time();
    if (prog->num_of_philos == 1)
    {
        print_msg(philo, philo->id, "has taken a fork\n");
        ft_usleep(prog->time_to_die);
        return;
    }
    if (prog->num_of_philos % 2 == 1)  // fixing if num philos even take some time 
    ft_usleep(20);
    // for odd philo lock left fork first, then right fork
    if (philo->id % 2 != 0)
    {
        pthread_mutex_lock(philo->l_fork);
        print_msg(philo, philo->id, "is taken a fork\n");
        pthread_mutex_lock(philo->r_fork);
        print_msg(philo, philo->id, "is taken a fork\n");
    }
    else
    {
        // for even philo lock right fork first, then left fork
        pthread_mutex_lock(philo->r_fork);
        print_msg(philo, philo->id, "is taken a fork\n");
        pthread_mutex_lock(philo->l_fork);
        print_msg(philo, philo->id, "is taken a fork\n");
    }

    pthread_mutex_lock(philo->meal_lock);
    philo->eating = 1;
    philo->last_meal = get_time();  // update last_meal before printing
    pthread_mutex_unlock(philo->meal_lock);
    print_msg(philo, philo->id, "is eating\n");
    // ft_usleep(prog->time_to_eat);

    while(!dead_loop(philo))    // fixing if time to eat too long
    {
        if(get_time() - eat_start >= (size_t)philo->prog->time_to_eat)
            break;
        usleep(1000);
    }
    pthread_mutex_lock(philo->meal_lock);
    philo->meals_eaten++;
    philo->eating = 0;
    pthread_mutex_unlock(philo->meal_lock);
    // Unlock forks in reverse order of acquisition
    if (philo->id % 2 != 0)
    {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
    }
    else
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
    }
    // pthread_mutex_unlock(philo->l_fork);
    // pthread_mutex_unlock(philo->r_fork);
}

