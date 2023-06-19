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
	int					eat_counter;
	t_time				time;
	pthread_mutex_t		var_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		*fork_mutex;
}						t_var;

typedef struct t_philo
{
	int					n_philo;
	int					next_philo;
	long				delay;
	long				eat_marker;
	long				time_marker;
	struct timeval		delay_marker;
	t_time				*life_time;
	t_var				*var;
	pthread_t			thread;
}						t_philo;

//philo
t_var		*struct_init_var(int argc, char **argv);
t_philo		*struct_init_philo(t_var *var);
int			thread_init(t_philo *philo);
int			thread_join(t_philo *philo, pthread_t tracker);

//philo_status
void		taking_forks(t_philo *philo);
int			eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		*thread_routine(void *arg);

//philo_utils
void		*tracker_routine(void *arg);
void		timestamp(t_philo *philo, char *message);
long		get_time(t_philo *philo, struct timeval start, struct timeval end);
void		sleeper(t_philo *philo, long timer);
void		add_delay(t_philo *philo);


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

Test: Con usleep(500) y sin thinking time.

./philo 5 800 200 200		-> no debe morir	-		OK			5/5	
./philo 4 410 200 200		-> no debe morir			OK			5/5	
./philo 3 310 100 100		-> no debe morir			OK			5/5		
./philo 5 600 150 150		-> no debe morir			OK			5/5		
./philo 2 210 100 100		-> no debe morir	-		OK			5/5
./philo 2 200 60 60 1

./philo 100 4000 60 60		-> no debe morir			OK			5/5	
./philo 150 4000 60 60		-> no debe morir			OK			5/5
./philo 200 4000 60 60		-> no debe morir			OK			5/5
./philo 200 4000 120 60		-> no debe morir	-		OK			5/5
./philo 200 4000 500 500	-> no debe morir			OK

./philo 2 200 60 60 0 		-> debe morir
./philo 1 800 200 200		-> debe morir				OK			5/5
./philo 4 200 205 200		-> debe morir				OK			5/5
./philo 100 800 200 200		-> debe morir		-		OK			5/5
./philo 105 800 200 200		-> debe morir		-		OK			5/5
./philo 200 800 200 200		-> debe morir		-		OK			5/5
./philo 4 310 200 100		-> debe morir				OK			5/5
./philo 200 2000 200 200	-> debe morir		-		OK			5/5

*/

//Implementar función del tiempo
//Arreglar parseo -> mallocs no protegidos
//Ver si algunos mutex etc... se pueden hacer sin reservar memoria y pasandole la dirección de memoria simplemente
//Quizás convenga tener taking forks y eating en una misma función.
//Es posible que el problema venga del cálculo del tiempo?
