#include "philo.h"

#define MAX_PHILOS 200  // set maximum philos number

int main(int argc, char **argv)
{
    t_philo philos[MAX_PHILOS];
    pthread_mutex_t forks[MAX_PHILOS];
    t_program prog;
    // int i;

    // i = 0;
    if (argc != 5 && argc != 6) // num philo/ time dead/ time eat / time sleep / num meals
        print_error(1, "Error : number of arguments is not correct\n");
    // prog.num_of_philos = ft_atoi(argv[1]);
    // prog.time_to_die = ft_atoi(argv[2]);
    // prog.time_to_eat = ft_atoi(argv[3]);
    // prog.time_to_sleep = ft_atoi(argv[4]);
    // prog.num_times_to_eat = -1;   // keep eating indefinitely
    // if(prog.num_of_philos == -1)
    //     print_error(1, "Error : invalide number of philos\n");
    // if(prog.time_to_die == -1)
    //     print_error(1, "Error : invalide time to die\n");
    // if(prog.time_to_eat == -1)
    //     print_error(1, "Error : invalide time to eat\n");
    // if(prog.time_to_sleep == -1)
    //     print_error(1, "Error : invalide time to sleep\n");
    // if (prog.num_of_philos < 0 || prog.num_of_philos > 200)
    //     print_error(1, "Error : invalide number of philos\n");
    // if (argv[5])
    //     prog.num_times_to_eat = ft_atoi(argv[5]);
    // if (prog.time_to_die < 60 || prog.time_to_eat < 60 || prog.time_to_sleep < 60)
    //     print_error(1, "Error : (time to die/time to eat/time to sleep) must be 60 or greater\n");
    prog.philos = philos;
    // prog.forks = forks;
    init_prog(&prog, philos);
    init_forks(forks, ft_atoi(argv[1]));
    init_philos(&prog, philos,forks, argv);
    creat_threads(&prog);

}