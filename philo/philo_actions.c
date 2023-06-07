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

void	taking_forks(t_philo *philo)
{
	int	next_philo;

	if (philo->var->flag != 0)
	{
		next_philo = philo->n_philo;
		if (philo->n_philo == philo->var->n_philos)
			next_philo = 0;
		pthread_mutex_lock(&philo->var->fork_mutex[philo->n_philo - 1]);
		pthread_mutex_lock(&philo->var->fork_mutex[next_philo]);
		if (philo->var->flag != 0)
			timestamp(philo, "has taken a fork");
		else
		{
			pthread_mutex_unlock(&philo->var->fork_mutex[philo->n_philo - 1]);
			pthread_mutex_unlock(&philo->var->fork_mutex[next_philo]);
		}
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
		memset((void *)&philo->life_time->t_start, 0, sizeof(struct timeval));
		gettimeofday(&philo->life_time->t_start, NULL);
		timestamp(philo, "is eating");
		usleep((philo->var->t_eat * 1000));
		philo->eat_counter++;
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
		timestamp(philo, "is thinking");
}

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

		pthread_mutex_lock(philo->var->write_mutex);
		//printf("tracker phil %d = %ld\n", philo[i].n_philo, tracker);
		pthread_mutex_unlock(philo->var->write_mutex);

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
//Destruir array de mutex.
