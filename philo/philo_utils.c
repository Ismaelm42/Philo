/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:34 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/26 12:59:01 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeper(t_philo *philo, long timer)
{
	struct timeval	t_end;
	struct timeval	t_start;
	long			time;

	time = 0;
	gettimeofday(&t_start, NULL);
	while (time < timer)
	{
		gettimeofday(&t_end, NULL);
		time = get_time(philo, t_start, t_end);
	}
}

void	timestamp(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->var->mutex);
	gettimeofday(&philo->var->time.t_end, NULL);
	philo->time_marker = get_time(philo, philo->var->time.t_start, \
	philo->var->time.t_end);
	printf("%ld ms %d %s\n", philo->time_marker, philo->philo, message);
	pthread_mutex_unlock(&philo->var->mutex);
}

long	get_time(t_philo *philo, struct timeval start, struct timeval end)
{
	long	start_time;
	long	end_time;
	long	time;

	start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	if (start_time == 0)
	{
		start_time = philo->var->time.t_start.tv_sec * 1000 + \
		philo->var->time.t_start.tv_usec / 1000;
	}
	end_time = (end.tv_sec * 1000) + (end.tv_usec / 1000);
	time = end_time - start_time;
	return (time);
}

void	add_delay(t_philo *philo, struct timeval start_time, int position)
{
	long	offset;

	pthread_mutex_lock(&philo->var->mutex);
	gettimeofday(&philo->delay_marker, NULL);
	offset = get_time(philo, start_time, philo->delay_marker);
	philo->delay = (philo->var->time_to_death - \
	philo->var->time_to_eat - offset) / 2;
	if (position == 0 && philo->delay <= 0)
		philo->delay = 1;
	if (position == 1 && philo->delay <= 0)
		philo->delay = 0;
	pthread_mutex_unlock(&philo->var->mutex);
	sleeper(philo, philo->delay);
}
