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

	if (philo->var->n_philos == 1)
		usleep((philo->var->t_death + 100) * 1000);
	else
	{
		next_philo = philo->n_philo;
		if (philo->n_philo == philo->var->n_philos)
			next_philo = 0;
		if (philo->n_philo % 2 == 0)
		{
			pthread_mutex_lock(&philo->var->fork_mtx[next_philo]);
			philo->unlock_right = 1;
			if (philo->var->flag != 0)
				timestamp(philo, "has taken a fork");
			pthread_mutex_lock(&philo->var->fork_mtx[philo->n_philo - 1]);
			philo->unlock_left = 1;
			if (philo->var->flag != 0)
				timestamp(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philo->var->fork_mtx[philo->n_philo - 1]);
			philo->unlock_left = 1;
			if (philo->var->flag != 0)
				timestamp(philo, "has taken a fork");
			pthread_mutex_lock(&philo->var->fork_mtx[next_philo]);
			philo->unlock_right = 1;
			if (philo->var->flag != 0)
				timestamp(philo, "has taken a fork");
		}
	}
}

void	eating(t_philo *philo)
{
	int	next_philo;

	next_philo = philo->n_philo;
	if (philo->n_philo == philo->var->n_philos)
		next_philo = 0;
	if (philo->var->flag != 0)
	{
		memset((void *)&philo->life_time->t_start, 0, sizeof(struct timeval));
		gettimeofday(&philo->life_time->t_start, NULL);
		timestamp(philo, "is eating");
		usleep(philo->var->t_eat * 1000);
		philo->eat_counter++;
	}
	if (philo->unlock_left == 1)
		pthread_mutex_unlock(&philo->var->fork_mtx[philo->n_philo - 1]);
	if (philo->unlock_right == 1)
		pthread_mutex_unlock(&philo->var->fork_mtx[next_philo]);
	philo->unlock_left = 0;
	philo->unlock_right = 0;
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
	long	time;

	if (philo->var->flag != 0)
	{
		timestamp(philo, "is thinking");
		time = get_time(philo);

		pthread_mutex_lock(philo->var->write_mtx);
		printf("%d time = %ld\n", philo->n_philo, time);
		pthread_mutex_unlock(philo->var->write_mtx);

		if (time < philo->var->t_eat + philo->var->t_eat + 10)
			usleep((philo->var->t_death - philo->var->t_eat \
			- philo->var->t_sleep) / 2);
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
			usleep(sleep_time);
	}
	while (philo->var->flag != 0)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
