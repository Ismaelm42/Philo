/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:35:49 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/08 19:17:06 by imoro-sa         ###   ########.fr       */
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

typedef struct s_time
{
	struct timeval		t_start;
	struct timeval		t_end;

}						t_time;

typedef struct s_var
{
	long				n_philos;
	long				t_death;
	long				t_eat;
	long				t_sleep;
	long				n_eat;
	int					flag;
	t_time				time;
	pthread_mutex_t		*write_mtx;
	pthread_mutex_t		*eat_mtx;
	pthread_mutex_t		*fork_mtx;
}						t_var;

typedef struct t_philo
{
	int					n_philo;
	int					n_fork;
	int					unlock_left;
	int					unlock_right;
	long				time_sec;
	long				time_usec;
	long				time_mark;
	long				eat_counter;
	t_time				*life_time;
	pthread_t			thread;
	t_var				*var;
}						t_philo;

//philo
t_var		*struct_init_var(int argc, char **argv);
t_philo		*struct_init_philo(t_var *var);
int			thread_init(t_philo *philo);
int			thread_join(t_philo *philo, pthread_t tracker);
int			main(int argc, char **argv);

//philo_status
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		*thread_routine(void *arg);

//philo_utils
void		*tracker_routine(void *arg);
void		timestamp(t_philo *philo, char *message);
long		get_time(t_philo *philo);
void		sleep_ms(t_philo *philo, long milliseconds);


//philo_parse_utils
int			error(char *str);
long		long_atoi(char *str, int *flag);
void		deallocate(t_philo *philo, t_var *var);

	//leaks
void		ft_leaks(void);

#endif

	// 1s = 1000 ms;		milisegundos
	// 1s = 1000000 us;		microsegundos

//Pruebas:

//1 800 200 200 -> Not eat and die.
//5 800 200 200 -> No philosopher shoud die.
//5 800 200 200 7 -> No philosopher shoud die and simulation stops at 7 meals.
//4 410 200 200 -> No philosopher should die.
//4 310 200 100 -> One philosopher should die.

/*

Test: 

./philo 5 800 200 200	-> no debe morir			OK
./philo 5 800 200 200 7	-> no debe morir			OK
./philo 4 410 200 200	-> no debe morir			OK
./philo 3 310 100 100	-> no debe morir			OK
./philo 5 800 200 200	-> no debe morir			OK
./philo 5 600 150 150	-> no debe morir			OK
./philo 2 210 100 100	-> no debe morir			OK

./philo 1 800 200 200	-> debe morir				OK
./philo 4 200 205 200	-> debe morir				OK
./philo 100 800 200 200	-> debe morir				OK
./philo 105 800 200 200	-> debe morir				OK
./philo 200 800 200 200	-> debe morir				OK
./philo 4 310 200 100	-> debe morir				OK

*/
