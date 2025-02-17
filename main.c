#include "philo.h"

#define MAX_PHILOS 200  // set maximum philos number

int main(int argc, char **argv)
{
    t_philo philos[MAX_PHILOS];
    pthread_mutex_t forks[MAX_PHILOS];
    t_program prog;

    if (argc != 5 && argc != 6) // num philo/ time dead/ time eat / time sleep / num meals
        print_error(1, "Error : number of arguments is not correct\n");
    prog.philos = philos;
    init_prog(&prog, philos);
    init_forks(forks, ft_atoi(argv[1]));
    init_philos(&prog, philos,forks, argv);
    creat_threads(&prog);
}