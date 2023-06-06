/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:35:49 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 14:57:00 by imoro-sa         ###   ########.fr       */
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
	pthread_mutex_t		*write_mutex;
	pthread_mutex_t		*fork_mutex;
}						t_var;

typedef struct t_philo
{
	int					n_philo;
	int					n_fork;
	long				time_sec;
	long				time_usec;
	long				time_mark;
	long				eat_counter;
	t_time				*life_time;
	pthread_t			thread;
	t_var				*var;
}						t_philo;

	//philo
void		*thread_routine(void *arg);

	//philo_parse
t_var		*struct_init_var(int argc, char **argv);
t_philo		*struct_init_philo(t_var *var);
int			thread_init(t_philo *philo, t_var *var);

	//philo_parse_utils
int			error(char *str);
long		long_atoi(char *str, int *flag);
void		deallocate(t_philo *philo);
void		timestamp(t_philo *philo, char *message);
long		get_time(t_philo *philo);

	//philo_actions
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		*life_tracker(void *arg);


#endif

	// 1s = 1000 ms;		milisegundos
	// 1s = 1000000 us;		microsegundos

//Crear funciones para eat, sleep, think.
//Think es una función de espera en la que se puede quedar el filo si su tenedor lo están utilizando.
//Será necesario otro mutex en la struct para proteger el estado de los tenedores.
//Cómo recoger el tiempo? Debería ser un sumatorio con el total del tiempo transcurrido hasta comer y memset.
//Utilizar una función para realizar el write


// void	*routine(void *arg)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)arg;
// 	pthread_mutex_lock(philo->var->write_mutex);
// 	gettimeofday(&philo->var->t_start, NULL);
// 	putnbr(philo->n_philo);
// 	write(1, "\n", 1);
// 	gettimeofday(&philo->var->t_end, NULL);
// 	get_time(philo);
// 	pthread_mutex_unlock(philo->var->write_mutex);
// 	return (NULL);
// }


// void	eating(t_philo *philo)
// {
// 	pthread_mutex_init(&philo->var->fork_mutex[philo->n_philo], NULL);
// 	pthread_mutex_init(&philo->var->fork_mutex[philo->n_philo + 1], NULL);
// 	pthread_mutex_init(philo->var->write_mutex, NULL);
// 	printf("get_time-> %d is eating\n", philo->n_philo);
// 	pthread_mutex_destroy(philo->var->write_mutex);
// 	usleep((long)&philo->var->t_eat);
// 	pthread_mutex_destroy(&philo->var->fork_mutex[philo->n_philo]);
// 	pthread_mutex_destroy(&philo->var->fork_mutex[philo->n_philo + 1]);
// }
