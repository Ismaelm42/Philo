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

void	eating(t_philo *philo)
{
	int	next_philo;

	if (philo->var->n_philos == 1)
		usleep((philo->var->t_death + 100) * 1000);
	else
	{
		next_philo = philo->n_philo;
		if (philo->n_philo == philo->var->n_philos)
			next_philo = 0;

		pthread_mutex_lock(philo->var->eat_mtx);
		pthread_mutex_lock(&philo->var->fork_mtx[philo->n_philo - 1]);
		if (philo->var->flag != 0)
			timestamp(philo, "has taken a fork");
		pthread_mutex_unlock(philo->var->eat_mtx);
		pthread_mutex_lock(&philo->var->fork_mtx[next_philo]);
		if (philo->var->flag != 0)
		{
			timestamp(philo, "has taken a fork");
			gettimeofday(&philo->life_time->t_start, NULL);
			timestamp(philo, "is eating");
			usleep(philo->var->t_eat * 1000);
			philo->eat_counter++;
		}
		pthread_mutex_unlock(&philo->var->fork_mtx[philo->n_philo - 1]);
		pthread_mutex_unlock(&philo->var->fork_mtx[next_philo]);
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
	long	pre_sleep;

	if (philo->var->flag != 0)
	{
		timestamp(philo, "is thinking");
		pre_sleep = (philo->var->t_death - philo->var->t_eat \
			- philo->var->t_sleep) / 2;
		if (pre_sleep > 0)
			usleep(pre_sleep);
	}
}

void	*thread_routine(void *arg)
{
	t_philo		*philo;
	long		sleep_time;

	philo = (t_philo *)arg;
	if (philo->n_philo % 2 == 0)
	{
		sleep_time = (philo->var->t_death - philo->var->t_eat \
			- philo->var->t_sleep) / 2;
		if (sleep_time >= 0)
			usleep(sleep_time); //500
	}
	while (philo->var->flag != 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
