/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:47:54 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/26 12:38:01 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->counter_mutex);
	if (philo->var->eat_counter == philo->var->nbr_philos)
	{
		pthread_mutex_unlock(&philo->var->counter_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->var->counter_mutex);
	return (1);
}

void	*tracker_routine(void *arg)
{
	t_philo			*philo;
	int				i;

	philo = (t_philo *)arg;
	philo->var->tracker = 0;
	i = 0;
	while (philo->var->tracker <= philo->var->time_to_death)
	{
		if (i == philo->var->nbr_philos)
			i = 0;
		if (eat_check(philo) == 0)
			break ;
		usleep(1);
		gettimeofday(&philo->var->time_tracker.t_end, NULL);
		philo->var->time_tracker.t_start = philo[i].life_cycle->t_start;
		philo->var->tracker = get_time(philo, philo->var->time_tracker.t_start, \
		philo->var->time_tracker.t_end);
		i++;
	}
	pthread_mutex_lock(&philo->var->flag_mutex);
	philo->var->flag = 0;
	pthread_mutex_unlock(&philo->var->flag_mutex);
	if (philo->var->tracker >= philo->var->time_to_death)
		timestamp(&philo[i - 1], "\x1b[31mdied\x1b[0m");
	return (NULL);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo % 2 == 0)
		add_delay(philo, philo->var->time.t_start, 0);
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
