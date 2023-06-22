/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:34 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/22 15:59:21 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*tracker_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	t_end;
	long			tracker;
	int				i;

	philo = (t_philo *)arg;
	tracker = 0;
	i = 0;
	while (tracker < philo->var->t_death)
	{
		if (i == philo->var->n_philos)
			i = 0;
		//mutex
		pthread_mutex_lock(&philo->var->counter_mutex);
		if (philo->var->eat_counter == philo->var->n_philos)
		{
			pthread_mutex_unlock(&philo->var->counter_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->var->counter_mutex);
		//mutex
		usleep(1);
		gettimeofday(&t_end, NULL);
		tracker = get_time(philo, philo[i].life_time->t_start, t_end);
		i++;
	}
	//mutex
	pthread_mutex_lock(&philo->var->flag_mutex);
	philo->var->flag = 0;
	pthread_mutex_unlock(&philo->var->flag_mutex);
	//mutex
	if (i == philo->var->n_philos)
		i = 1;
	if (tracker >= philo->var->t_death)
		timestamp(&philo[i - 1], "\x1b[31mdied\x1b[0m");
	return (NULL);
}
//puedo usar un mutex para routine pero para tracker, que comparte variables
//con otros hilos, tengo que usar otros mutex para esas variables.
//usleep protege get_time para que los tiempos no sean incongruentes.
//Imperativo dejarlo.
//Ya he comprobado muchas veces que si lo quito se va todo a la puta.

void	sleeper(t_philo *philo, long timer)
{
	struct timeval	t_end;
	struct timeval	t_start;
	long			time;

	time = 0;
	gettimeofday(&t_start, NULL);
	while (time < timer)
	{
		gettimeofday(&t_end, NULL);
		time = get_time(philo, t_start, t_end);
	}
}

void	timestamp(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->var->mutex);
	gettimeofday(&philo->var->time.t_end, NULL);
	philo->time_marker = get_time(philo, philo->var->time.t_start, \
	philo->var->time.t_end);
	printf("%ld ms %d %s\n", philo->time_marker, philo->n_philo, message);
	pthread_mutex_unlock(&philo->var->mutex);
}

long	get_time(t_philo *philo, struct timeval start, struct timeval end)
{
	long	start_time;
	long	end_time;
	long	time;

	start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	if (start_time == 0)
	{
		start_time = philo->var->time.t_start.tv_sec * 1000 + \
		philo->var->time.t_start.tv_usec / 1000;
	}
	end_time = (end.tv_sec * 1000) + (end.tv_usec / 1000);
	time = end_time - start_time;
	return (time);
}

void	add_delay(t_philo *philo, int loop)
{
	//mutex
	pthread_mutex_lock(&philo->var->mutex);
	gettimeofday(&philo->delay_marker, NULL);
	philo->delay = philo->var->t_death - get_time(philo, philo->var->time.t_start, philo->delay_marker);
	//Error aquí, corregir con el tiempo cuando entra en eating para renovar ese tiempo.
	//Cambiar la función para que recoja el tiempo no acumulativo, sino el de cada comida y en caso de que sea igual a 0 que coja el de var.
	//var->time.t_start debe ser igual a philo->life_time.t_start, si la última comida no existe, el tiempo debe ser entonces igual a var->time.t_start
	if (philo->delay < 0)
		philo->delay = 0;
	else if (philo->var->n_philos < 100)
		philo->delay /= 2;
	else
		philo->delay /= 4;
	pthread_mutex_unlock(&philo->var->mutex);
	//mutex
	sleeper(philo, philo->delay);
}
//Original: sleeper philo->life_time / 2;
