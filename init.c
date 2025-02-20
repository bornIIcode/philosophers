#include "philo.h"

int check_args(char **argv)
{
    int i;
    int j;

    i = 1;
    while(argv[i] != NULL)
    {
        j = 0;
        while(argv[i][j] != '\0')
        {
            while(argv[i][j] == '+' || argv[i][j] == '\t' || argv[i][j] == ' ')
                j++;
            if(!ft_isdigit(argv[i][j]))
                return(1);
            j++;
        }
        i++;
    }
    return(0);
}
void init_input(t_program *prog, char **argv)
{
  prog->num_of_philos = ft_atoi(argv[1]);
  prog->time_to_die = ft_atoi(argv[2]);
  prog->time_to_eat = ft_atoi(argv[3]);
  prog->time_to_sleep = ft_atoi(argv[4]);
  prog->num_times_to_eat = -1;   // keep eating indefinitely
  if(prog->num_of_philos <= -1 || prog->num_of_philos == 0)
      print_error(1, "Error : invalide number of philos\n");
  if(prog->time_to_die <= 0)
      print_error(1, "Error : invalide time to die\n");
  if(prog->time_to_eat <= 0)
      print_error(1, "Error : invalide time to eat\n");
  if(prog->time_to_sleep <= 0)
      print_error(1, "Error : invalide time to sleep\n");
  if (prog->num_of_philos < 0 || prog->num_of_philos > 200)
      print_error(1, "Error : invalide number of philos\n");
  if (argv[5])
  {
    prog->num_times_to_eat = ft_atoi(argv[5]);
    if(prog->num_times_to_eat <= 0)
        print_error(1, "Error : invalide number of times to eat\n");
  }
  if (prog->time_to_die < 60 || prog->time_to_eat < 60 || prog->time_to_sleep < 60)
      print_error(1, "Error : (time to die/time to eat/time to sleep) must be 60 or greater\n");
}

void init_prog(t_program *prog, t_philo *philo)
{
  prog->philos = philo;
  prog->dead_flag = 0;

  pthread_mutex_init(&prog->dead_lock, NULL);
  pthread_mutex_init(&prog->meal_lock, NULL);
  pthread_mutex_init(&prog->write_lock, NULL);
}

void init_philos(t_program *prog, t_philo *philo, pthread_mutex_t *forks, char **argv)
{
  int i;

  i = 0;
  while(i < ft_atoi(argv[1]))
  {
    philo[i].id = i + 1;
    philo[i].eating = 0;
    philo[i].meals_eaten = 0;
    philo[i].last_meal = get_time();
    philo[i].start_time = get_time();
    philo[i].dead = &prog->dead_flag;
    philo[i].write_lock = &prog->write_lock;
    philo[i].dead_lock = &prog->dead_lock;
    philo[i].meal_lock = &prog->meal_lock;
    philo[i].prog = prog;
    philo[i].l_fork = &forks[i];
    philo[i].r_fork = &forks[(i + 1) % prog->num_of_philos];

    // // For even philosophers, assign right fork first
    // if (i % 2 == 0)
    // {
    //     philo[i].r_fork = &forks[(i + 1) % prog->num_of_philos];  // right fork
    //     philo[i].l_fork = &forks[i];                             // left fork
    // }
    // // For odd philosophers, assign left fork first
    // else
    // {
    //     philo[i].l_fork = &forks[i];                          // left fork
    //     philo[i].r_fork = &forks[(i + 1) % prog->num_of_philos]; // right fork
    // }

    i++;
  }
}

void init_forks(pthread_mutex_t *forks, int num_philo)
{
	int i;

	i = 0;
	while(i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}