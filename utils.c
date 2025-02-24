#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if ((signe == 1 && result > INT_MAX) || (signe == -1 && result
				* signe < INT_MIN))
			return (-1);
		i++;
	}
	return (result * signe);
}

void	print_error(int flag, char *str)
{
	if (flag == 1)
	{
		write(2, str, strlen(str));
		exit(1);
	}
}

void	print_msg(t_philo *philo, int id, char *str)
{
	size_t	time;

	if (dead_loop(philo))
		return ;
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		print_error(2, "Error : gettimeofday/n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(100);
	return (0);
}

int	all_eat(t_program *prog)
{
	int	i;
	int	all_eat;

	if (prog->num_times_to_eat <= 0)
		return (0);
	i = 0;
	all_eat = prog->num_of_philos;
	pthread_mutex_lock(prog->philos[0].meal_lock);
	while (i < prog->num_of_philos)
	{
		if (prog->philos[i].meals_eaten < prog->num_times_to_eat)
			all_eat--;
		i++;
	}
	pthread_mutex_unlock(prog->philos[0].meal_lock);
	if (all_eat == 0)
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
