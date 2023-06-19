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
	if (philo->var->n_philos == 1 || philo->var->n_eat == 0)
		usleep((philo->var->t_death + 1) * 1000);
	else
	{
		pthread_mutex_lock(&philo->var->fork_mutex[philo->n_philo - 1]);
		if (philo->var->flag != 0)
			timestamp(philo, "has taken a fork");
		pthread_mutex_lock(&philo->var->fork_mutex[philo->next_philo]);
		if (philo->var->flag != 0)
			timestamp(philo, "has taken a fork");
	}
}

int	eating(t_philo *philo)
{
	if (philo->var->flag != 0)
	{
		gettimeofday(&philo->life_time->t_start, NULL);
		timestamp(philo, "is eating");
		sleeper(philo, philo->var->t_eat);
		philo->eat_marker++;
	}
	pthread_mutex_unlock(&philo->var->fork_mutex[philo->n_philo - 1]);
	pthread_mutex_unlock(&philo->var->fork_mutex[philo->next_philo]);
	if (philo->eat_marker == philo->var->n_eat)
	{
		pthread_mutex_lock(&philo->var->var_mutex);
		philo->var->eat_counter++;
		pthread_mutex_unlock(&philo->var->var_mutex);
		return (1);
	}
	return (0);
}

void	sleeping(t_philo *philo)
{	
	if (philo->var->flag != 0)
	{
		timestamp(philo, "is sleeping");
		sleeper(philo, philo->var->t_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->var->flag != 0)
	{
		timestamp(philo, "is thinking");
		add_delay(philo);
	}
}

void	*thread_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	philo->next_philo = philo->n_philo;
	if (philo->n_philo == philo->var->n_philos)
		philo->next_philo = 0;
	if (philo->n_philo % 2 == 0)
		add_delay(philo);
	while (philo->var->flag != 0)
	{
		taking_forks(philo);
		if (eating(philo) == 1)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
//Tener en cuenta valores negativos para sleeper etc.
//Función en Thinking con wait-time parece obligatoria
//para que esperen los que ya han comido.

//LO TIENES CASI MI BRO!!!!
