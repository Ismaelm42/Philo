/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:07 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 11:26:07 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0)
		len++;
	write(2, str, len);
	return (EXIT_FAILURE);
}

long	long_atoi(char *str, int *flag)
{
	int		i;
	long	sum;

	i = 0;
	sum = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (*flag = -1, sum);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (sum);
}
	//Si lo mantengo hasta el valor max de un int da segmentation fault.

void	deallocate(t_philo *philo)
{
	free(philo->var->write_mutex);
	free(philo->var->fork_mutex);
	free(philo->life_time);
	free(philo->var);
	free(philo);
}

void	timestamp(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->var->write_mutex);
	memset(&philo->var->time.t_end, 0, sizeof(struct timeval));
	gettimeofday(&philo->var->time.t_end, NULL);
	philo->time_sec = philo->var->time.t_end.tv_sec \
		- philo->var->time.t_start.tv_sec;
	philo->time_usec = philo->var->time.t_end.tv_usec \
		- philo->var->time.t_start.tv_usec;
	philo->time_mark = philo->time_sec * 1000 + philo->time_usec / 1000;
	printf("%ld ms\t%d %s\n", philo->time_mark, philo->n_philo, message);
	pthread_mutex_unlock(philo->var->write_mutex);
}
	//gettimeofday de life_time tmb y así aprovechar el mismo mutex.

long	get_time(t_philo *philo)
{
	long	time_sec;
	long	time_usec;
	long	time;

	memset(&philo->life_time->t_end, 0, sizeof(struct timeval));
	gettimeofday(&philo->life_time->t_end, NULL);
	if (philo->life_time->t_start.tv_usec == 0)
	{
		time_sec = philo->life_time->t_end.tv_sec \
			- philo->var->time.t_start.tv_sec;
		time_usec = philo->life_time->t_end.tv_usec \
			- philo->var->time.t_start.tv_usec;
	}
	else
	{
		time_sec = philo->life_time->t_end.tv_sec \
			- philo->life_time->t_start.tv_sec;
		time_usec = philo->life_time->t_end.tv_usec \
			- philo->life_time->t_start.tv_usec;
	}
	time = time_sec * 1000 + time_usec / 1000;
	return (time);
}
//El if añade la condición cuando life_time no ha sido aún inicializado y se toma el
//tiempo del comienzo del programa como referencia.
