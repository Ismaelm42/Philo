/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:35:49 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/22 15:21:47 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ARG_ERRN "invalid number of arguments\n"
# define ARG_ERR "invalid arguments\n"
# define THRD_ERR "thread failed\n"
# define MEM_ERR "malloc allocation failed\n"

typedef struct s_time
{
	struct timeval		t_start;
	struct timeval		t_end;
}						t_time;

typedef struct s_var
{
	long				nbr_philos;
	long				time_to_death;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_eat;
	int					flag;
	int					eat_counter;
	long				tracker;
	t_time				time;
	t_time				time_tracker;
	pthread_mutex_t		mutex;
	pthread_mutex_t		flag_mutex;
	pthread_mutex_t		counter_mutex;
	pthread_mutex_t		*fork_mutex;
}						t_var;

typedef struct t_philo
{
	int					philo;
	int					next_philo;
	long				delay;
	long				eat_marker;
	long				time_marker;
	struct timeval		delay_marker;
	t_time				*life_cycle;
	t_var				*var;
	pthread_t			thread;
}						t_philo;

//philo
t_var		*struct_init_var(int argc, char **argv);
t_philo		*struct_init_philo(t_var *var);
int			thread_init(t_philo *philo);
int			thread_join(t_philo *philo, pthread_t tracker);

//philo_status
int			taking_forks(t_philo *philo);
int			eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//philo_utils
void		timestamp(t_philo *philo, char *message);
long		get_time(t_philo *philo, struct timeval start, struct timeval end);
void		sleeper(t_philo *philo, long timer);
void		add_delay(t_philo *philo, struct timeval start_time);

//philo_parse_utils
int			error(char *str);
long		long_atoi(char *str, int *flag);
void		deallocate(t_philo *philo, t_var *var);
t_var		*fork_mutex_allocation(t_var *var);

//routine
int			eat_check(t_philo *philo);
void		*tracker_routine(void *arg);
void		*thread_routine(void *arg);


	//leaks
void		ft_leaks(void);

#endif

/*

Evaluation:

	1 800 200 200 -> Not eat and die.
	5 800 200 200 -> No philosopher shoud die.
	5 800 200 200 7 -> No philosopher shoud die and simulation stops at 7 meals.
	4 410 200 200 -> No philosopher should die.
	4 310 200 100 -> One philosopher should die.
	2 philo tests


./philo 5 800 200 200			-> no debería morir
./philo 4 410 200 200			-> no debería morir
./philo 3 310 100 100			-> no debería morir
./philo 3 301 100 100			-> no debería morir
./philo 5 600 150 150			-> no debería morir
./philo 2 210 100 100			-> no debería morir
./philo 2 200 100 100			-> debería morir
./philo 2 200  60  60  1	


./philo 100 4000  60 60			-> no debería morir
./philo 150 4000  60 60			-> no debería morir
./philo 200 4000  60 60			-> no debería morir
./philo 200 4000 120 60			-> no debería morir

./philo   2 200  60  60  0 		-> debería morir
./philo   4 200 205 200			-> debería morir
./philo   3 299 100 100			-> debería morir
./philo 100 800 300 200			-> debería morir
./philo 200 800 200 200			-> debería morir		
./philo   4 310 200 100			-> debería morir


Pruebas complejas	

./philo   3  300 100 100		-> no debería morir
./philo 100  800 100 100		-> debería morir		X
./philo 100  800 150 150		-> debería morir		X
./philo 200 1500 200 200 		-> debería morir		X
./philo 200 4000 500 500		-> no debería morir		X
./philo   2  200 100  99		-> no debería morir		X



Potential deadlock linux -> 	check MAC ./philo 3 200 205 200
											./philo 4 200 205 200

*/
