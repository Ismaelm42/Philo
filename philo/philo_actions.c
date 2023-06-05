/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:43:40 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 14:50:35 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	int	next_philo;

	if (philo->var->flag != 0)
	{
		next_philo = philo->n_philo;
		if (philo->n_philo == philo->var->n_philos)
			next_philo = 0;
		pthread_mutex_lock(&philo->var->fork_mutex[philo->n_philo - 1]);
		pthread_mutex_lock(&philo->var->fork_mutex[next_philo]);
		timestamp(philo, "has taken a fork");
		memset((void *)&philo->life_time->t_start, 0, sizeof(struct timeval));
		gettimeofday(&philo->life_time->t_start, NULL);
	}
}

void	eating(t_philo *philo)
{
	int	next_philo;

	if (philo->var->flag != 0)
	{
		next_philo = philo->n_philo;
		if (philo->n_philo == philo->var->n_philos)
			next_philo = 0;
		timestamp(philo, "is eating");
		usleep((philo->var->t_eat * 1000));
		pthread_mutex_unlock(&philo->var->fork_mutex[philo->n_philo - 1]);
		pthread_mutex_unlock(&philo->var->fork_mutex[next_philo]);
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->var->flag != 0)
	{
		timestamp(philo, "is sleeping");
		usleep(philo->var->t_sleep * 1000);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->var->flag != 0)
	{
		timestamp(philo, "is thinking");
	}
}

void	*life_tracker(void *arg)
{
	int			i;
	long		tracker;
	t_philo		*philo;

	i = 0;
	tracker = 0;
	philo = (t_philo *)arg;
	while (tracker < philo->var->t_death)
	{
		if (i == philo->var->n_philos)
			i = 0;
		usleep (1000 / philo->var->n_philos);
		tracker = get_time(&philo[i]);
		if (tracker > 98)
		{
			pthread_mutex_lock(philo->var->write_mutex);
			printf("%d tracker = %ld\n", philo[i].n_philo, tracker);
			pthread_mutex_unlock(philo->var->write_mutex);
		}
		i++;
	}
	philo->var->flag = 0;
	if (i == philo->var->n_philos - 1)
		i = 0;
	else
		i += -1;
	timestamp(&philo[i], "died");
	return ((void *)philo);
}
//Realizar un usleep de 2ms para imprimir el mensaje died el último.
//Simplificar el índice? Confunde y tengo que emplear dos líneas en ubicarlo.
//La función Usleep en este bucle ejecuta una vuelta entera en 1 ms.
//Usleep evita errores en las restas de get_time.
