#include "philo.h"

void init_input(t_program *prog, char **argv)
{
  prog->num_of_philos = ft_atoi(argv[1]);
  prog->time_to_die = ft_atoi(argv[2]);
  prog->time_to_eat = ft_atoi(argv[3]);
  prog->time_to_sleep = ft_atoi(argv[4]);
  prog->num_times_to_eat = -1;   // keep eating indefinitely
  if(prog->num_of_philos == -1)
      print_error(1, "Error : invalide number of philos\n");
  if(prog->time_to_die == -1)
      print_error(1, "Error : invalide time to die\n");
  if(prog->time_to_eat == -1)
      print_error(1, "Error : invalide time to eat\n");
  if(prog->time_to_sleep == -1)
      print_error(1, "Error : invalide time to sleep\n");
  if (prog->num_of_philos < 0 || prog->num_of_philos > 200)
      print_error(1, "Error : invalide number of philos\n");
  if (argv[5])
      prog->num_times_to_eat = ft_atoi(argv[5]);
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
    init_input(prog, argv);
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
    philo[i].r_fork = &forks[(i - 1) % prog->num_of_philos];
    // pthread_mutex_init(philo[i].l_fork, NULL);
    // pthread_mutex_init(philo[i].r_fork, NULL);
    // if (i == 0)
    // philo[i].r_fork = &forks[philo[i].num_of_philos - 1];
    // else
    // philo[i].r_fork = &forks[i - 1];
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