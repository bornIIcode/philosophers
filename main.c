#include "philo.h"

#define MAX_PHILOS 200  // set maximum philos number

int main(int argc, char **argv)
{
    t_philo philos[MAX_PHILOS];
    pthread_mutex_t forks[MAX_PHILOS];
    t_program prog;

    prog.philos = philos;
    if (argc != 5 && argc != 6) // num philo/ time dead/ time eat / time sleep / num meals
        print_error(1, "Error : number of arguments is not correct\n");
    if(check_args(argv) != 0)
        print_error(1, "Error : some argument not valid\n");
    init_input(&prog, argv);
    init_prog(&prog, philos);
    init_philos(&prog, philos,forks, argv);
    init_forks(forks, ft_atoi(argv[1]));
    creat_threads(&prog);
}
