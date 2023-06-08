/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:43:40 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/08 19:20:08 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	int	next_philo;

	if (philo->var->flag != 0)
	{
		if (philo->var->n_philos == 1)
			usleep((philo->var->t_death + 1) * 1000);
		else
		{
			next_philo = philo->n_philo;
			if (philo->n_philo == philo->var->n_philos)
				next_philo = 0;
			pthread_mutex_lock(&philo->var->fork_mtx[philo->n_philo - 1]);
			pthread_mutex_lock(&philo->var->fork_mtx[next_philo]);
			if (philo->var->flag != 0)
				timestamp(philo, "has taken a fork");
			else
			{
				pthread_mutex_unlock(&philo->var->fork_mtx[philo->n_philo - 1]);
				pthread_mutex_unlock(&philo->var->fork_mtx[next_philo]);
			}
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
		sleep_for(philo, philo->var->t_eat * 1000);/////////////////////////////
		philo->eat_counter++;
		pthread_mutex_unlock(&philo->var->fork_mtx[philo->n_philo - 1]);
		pthread_mutex_unlock(&philo->var->fork_mtx[next_philo]);
	}
}

void	sleeping(t_philo *philo)
{	
	if (philo->var->flag != 0)
	{
		timestamp(philo, "is sleeping");
		usleep(philo->var->t_sleep * 1000);///////////////////////////////////
	}
}

void	thinking(t_philo *philo)
{
	if (philo->var->flag != 0)
		timestamp(philo, "is thinking");
}

//Poner un usleep antes del if para evitar errores como
//2209 is eating / 2209 is thinking

void	*thread_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->n_philo % 2 == 0)
		usleep(100);
	while (philo->var->flag != 0)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
