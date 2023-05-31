/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:35:49 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/05/26 10:49:49 by imoro-sa         ###   ########.fr       */
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

typedef struct s_var
{
	int					n_philos;
	int					t_death;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					flag;
	struct timeval		t_start;
	struct timeval		t_end;
	pthread_mutex_t		*mutex;
}						t_var;

typedef struct t_philo
{
	int					n_fork;
	int					n_philo;
	pthread_t			thread;
	t_var				*var;
}						t_philo;

	//philo
void	*routine(void *arg);
int		thread_init(t_philo *philo, t_var *var);

	//philo_parse
t_var	*struct_init_var(int argc, char **argv);
t_philo	*struct_init_philo(t_var *var);


	//philo_parse_utils
int		print(char *str, int fd, int exit);
int		ctrl_atoi(char *str, int *flag);
void	ft_free(t_philo *philo);
void	test(int time);

void	putnbr(int time);
void	get_time(t_philo *philo);





#endif

	// 1s = 1000 ms;		milisegundos
	// 1s = 1000000 us;		microsegundos

//Crear funciones para eat, sleep, think.
//Think es una función de espera en la que se puede quedar el filo si su tenedor lo están utilizando.
//Será necesario otro mutex en la struct para proteger el estado de los tenedores.
//Cómo recoger el tiempo? Debería ser un sumatorio con el total del tiempo transcurrido hasta comer y memset.

