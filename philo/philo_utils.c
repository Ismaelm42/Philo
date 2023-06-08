/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:34 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/08 19:17:11 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_tracker(void *arg)
{
	int			i;
	long		tracker;
	long		counter;
	t_philo		*philo;

	i = 0;
	tracker = 0;
	counter = 0;
	philo = (t_philo *)arg;
	while (tracker < philo->var->t_death && counter != philo->var->n_philos)
	{
		if (i == philo->var->n_philos)
			i = 0;
		usleep (1000 / philo->var->n_philos);
		tracker = get_time(&philo[i]);
		if (philo[i].eat_counter == philo->var->n_eat)
			counter++;
		i++;
	}
	philo->var->flag = 0;
	if (i == philo->var->n_philos)
		i = 1;
	if (tracker >= philo->var->t_death)
		timestamp(&philo[i - 1], "died");
	return (NULL);
}
//Realizar un usleep de 2ms para imprimir el mensaje died el último.
//La función Usleep en este bucle ejecuta una vuelta entera en 1 ms.
//Usleep evita errores en las restas de get_time que hacen que el tiempo
//supere el máximo cuando no lo hace.

void	timestamp(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->var->write_mtx);
	memset(&philo->var->time.t_end, 0, sizeof(struct timeval));
	gettimeofday(&philo->var->time.t_end, NULL);
	philo->time_sec = philo->var->time.t_end.tv_sec \
		- philo->var->time.t_start.tv_sec;
	philo->time_usec = philo->var->time.t_end.tv_usec \
		- philo->var->time.t_start.tv_usec;
	philo->time_mark = philo->time_sec * 1000 + philo->time_usec / 1000;
	printf("%ld ms %d %s\n", philo->time_mark, philo->n_philo, message);
	pthread_mutex_unlock(philo->var->write_mtx);
}
//gettimeofday de life_time tmb y así aprovechar el mismo mtx.

long	get_time(t_philo *philo)
{
	long	time_sec;
	long	time_usec;
	long	time;

	memset(&philo->life_time->t_end, 0, sizeof(struct timeval));
	gettimeofday(&philo->life_time->t_end, NULL);
	if (philo->life_time->t_start.tv_usec == 0)
	{
		time_sec = philo->life_time->t_end.tv_sec \
			- philo->var->time.t_start.tv_sec;
		time_usec = philo->life_time->t_end.tv_usec \
			- philo->var->time.t_start.tv_usec;
	}
	else
	{
		time_sec = philo->life_time->t_end.tv_sec \
			- philo->life_time->t_start.tv_sec;
		time_usec = philo->life_time->t_end.tv_usec \
			- philo->life_time->t_start.tv_usec;
	}
	time = time_sec * 1000 + time_usec / 1000;
	return (time);
}

void	sleep_for(t_philo *philo, long milliseconds)
{
	struct timeval	t_start;
	struct timeval	t_end;
	long			time;

	time = 0;
	gettimeofday(&t_start, NULL);
	while (time < milliseconds)
	{
		if (philo->var->flag == 0)
			break ;
		usleep(200);
		if (philo->var->flag == 0)
			break ;
		gettimeofday(&t_end, NULL);
		time = (t_end.tv_sec - t_start.tv_sec) * 1000 \
			+ (t_end.tv_usec - t_start.tv_usec) * 1000;
	}
}
