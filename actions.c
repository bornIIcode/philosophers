#include "philo.h"

void	thinking(t_philo *philo)
{
	print_msg(philo, philo->id, "is thinking\n");
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, philo->id, "is sleeping\n");
	ft_usleep(philo->prog->time_to_sleep);
}

void	eating(t_philo *philo)
{
	t_program	*prog;

	prog = philo->prog;

	if (prog->num_of_philos % 2 == 1)
		ft_usleep(1);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, philo->id, "has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, philo->id, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, philo->id, "has taken a fork\n");
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, philo->id, "has taken a fork\n");
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_msg(philo, philo->id, "is eating\n");
	ft_usleep(prog->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
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
}
