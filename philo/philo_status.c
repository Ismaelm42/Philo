/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:43:40 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/22 15:19:03 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_forks(t_philo *philo)
{
	if (philo->var->n_philos == 1 || philo->var->n_eat == 0)
	{
		usleep((philo->var->t_death + 1) * 1000);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->var->fork_mutex[philo->n_philo - 1]);
		pthread_mutex_lock(&philo->var->flag_mutex);
		if (philo->var->flag != 0)
		{
			pthread_mutex_unlock(&philo->var->flag_mutex);
			timestamp(philo, "has taken a fork");
		}
		else
			pthread_mutex_unlock(&philo->var->flag_mutex);
		pthread_mutex_lock(&philo->var->fork_mutex[philo->next_philo]);
		pthread_mutex_lock(&philo->var->flag_mutex);
		if (philo->var->flag != 0)
		{
			pthread_mutex_unlock(&philo->var->flag_mutex);
			timestamp(philo, "has taken a fork");
		}
		else
			pthread_mutex_unlock(&philo->var->flag_mutex);
	}
	return (0);
}
//sync que puede ser un posible problema. No debería ser muy grave.

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->flag_mutex);
	if (philo->var->flag != 0)
	{
		pthread_mutex_unlock(&philo->var->flag_mutex);
		gettimeofday(&philo->life_time->t_start, NULL);
		timestamp(philo, "is eating");
		sleeper(philo, philo->var->t_eat);
		philo->eat_marker++;
	}
	else
		pthread_mutex_unlock(&philo->var->flag_mutex);
	pthread_mutex_unlock(&philo->var->fork_mutex[philo->n_philo - 1]);
	pthread_mutex_unlock(&philo->var->fork_mutex[philo->next_philo]);
	if (philo->eat_marker == philo->var->n_eat)
	{
		pthread_mutex_lock(&philo->var->counter_mutex);
		philo->var->eat_counter++;
		pthread_mutex_unlock(&philo->var->counter_mutex);
		return (1);
	}
	return (0);
}

void	sleeping(t_philo *philo)
{	
	pthread_mutex_lock(&philo->var->flag_mutex);
	if (philo->var->flag != 0)
	{
		pthread_mutex_unlock(&philo->var->flag_mutex);
		timestamp(philo, "is sleeping");
		sleeper(philo, philo->var->t_sleep);
	}
	else
		pthread_mutex_unlock(&philo->var->flag_mutex);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->flag_mutex);
	if (philo->var->flag != 0)
	{
		pthread_mutex_unlock(&philo->var->flag_mutex);
		timestamp(philo, "is thinking");
		add_delay(philo, 1);
	}
	else
		pthread_mutex_unlock(&philo->var->flag_mutex);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->next_philo = philo->n_philo;
	if (philo->n_philo == philo->var->n_philos)
		philo->next_philo = 0;
	if (philo->n_philo % 2 != 0)
		add_delay(philo, 0);
	while (1)
	{
		pthread_mutex_lock(&philo->var->flag_mutex);
		if (philo->var->flag == 0)
		{
			pthread_mutex_unlock(&philo->var->flag_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(&philo->var->flag_mutex);
		if (taking_forks(philo) == 1)
			break ;
		if (eating(philo) == 1)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
