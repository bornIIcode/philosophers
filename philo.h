/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:30:20 by ytabia            #+#    #+#             */
/*   Updated: 2025/02/25 11:50:44 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MAX_PHILOS 400
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_program;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	int					meals_eaten;
	size_t				start_time;
	size_t				last_meal;
	int					*dead;
	int					num_of_philos;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	struct s_program	*prog;
}						t_philo;
typedef struct s_program
{
	int					dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_times_to_eat;
}						t_program;

int						creat_threads(t_program *prog);
void					print_error(int flag, char *str);
void					print_msg(t_philo *philo, int id, char *str);
size_t					get_time(void);
int						ft_atoi(const char *str);
size_t					ft_strlen(const char *str);
int						ft_isdigit(int c);
int						ft_usleep(size_t milliseconds);
int						dead_loop(t_philo *philo);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);
void					*philo_routine(void *args);
int						all_eat(t_program *prog);
void					*dead_monitor(void *args);
void					init_input(t_program *prog, char **argv);
void					init_prog(t_program *prog);
void					init_philos(t_program *prog, t_philo *philo,
							pthread_mutex_t *forks, char **argv);
void					init_forks(pthread_mutex_t *forks, int num_philo);
int						check_if_dead(t_program *prog);
int						philo_dead(t_philo *philo, size_t time_to_die);
int						check_args(char **argv);

#endif