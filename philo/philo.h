/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:35:49 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/26 14:05:34 by imoro-sa         ###   ########.fr       */
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

t_var		*struct_init_var(int argc, char **argv);
t_philo		*struct_init_philo(t_var *var);
int			thread_init(t_philo *philo);
int			thread_join(t_philo *philo, pthread_t tracker);
int			taking_forks(t_philo *philo);
int			eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		timestamp(t_philo *philo, char *message);
long		get_time(t_philo *philo, struct timeval start, struct timeval end);
void		sleeper(t_philo *philo, long timer);
void		add_delay(t_philo *philo, struct timeval start_time, int position);
int			error(char *str);
long		long_atoi(char *str, int *flag);
void		deallocate(t_philo *philo, t_var *var);
t_var		*fork_mutex_allocation(t_var *var);
int			eat_check(t_philo *philo);
void		*tracker_routine(void *arg);
void		*thread_routine(void *arg);

#endif
