/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:43:40 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/26 12:38:40 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_forks(t_philo *philo)
{
	if (philo->var->nbr_philos == 1 || philo->var->nbr_eat == 0)
		return (sleeper(philo, (philo->var->time_to_death + 1)), 1);
	else
	{
		pthread_mutex_lock(&philo->var->fork_mutex[philo->philo - 1]);
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

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->flag_mutex);
	if (philo->var->flag != 0)
	{
		pthread_mutex_unlock(&philo->var->flag_mutex);
		gettimeofday(&philo->life_cycle->t_start, NULL);
		timestamp(philo, "is eating");
		sleeper(philo, philo->var->time_to_eat);
		philo->eat_marker++;
	}
	else
		pthread_mutex_unlock(&philo->var->flag_mutex);
	pthread_mutex_unlock(&philo->var->fork_mutex[philo->philo - 1]);
	pthread_mutex_unlock(&philo->var->fork_mutex[philo->next_philo]);
	if (philo->eat_marker == philo->var->nbr_eat)
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
		sleeper(philo, philo->var->time_to_sleep);
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
		add_delay(philo, philo->life_cycle->t_start, 1);
	}
	else
		pthread_mutex_unlock(&philo->var->flag_mutex);
}
