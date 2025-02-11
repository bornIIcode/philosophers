#include "philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				signe;
	long		    result;

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
        if ((signe == 1 && result > INT_MAX) || 
            (signe == -1 && result * signe < INT_MIN))
            return (-1);
		i++;
	}
	return (result * signe);
}

int main(int argc, char **argv)
{
    int i;
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_meals;

    if (argc != 5 && argc != 6) // num philo/ time dead/ time eat / time sleep / num meals
        return (1);
    i = 1;
    num_philo = atoi(argv[1]);
    time_to_die = atoi(argv[2]);
    time_to_eat = atoi(argv[3]);
    time_to_sleep = atoi(argv[4]);
    num_meals = -1;   // keep eating indefinitely
    if(num_philo == -1 || time_to_die == -1 || time_to_eat == -1 || time_to_sleep == -1)
        return(1);
    if (num_philo < 0 || num_philo > 200)
        return (1);
    if (argc == 6)
        num_meals = atoi(argv[5]);
    if (time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
        return (1);
}