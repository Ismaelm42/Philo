/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:35:45 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 14:50:09 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	eating(philo);
	sleeping(philo);
	thinking(philo);
}
//Mutex no funciona. Probar a iniciarlos antes de pthread_create.

int	thread_init(t_philo *philo, t_var *var)
{
	int				i;

	pthread_mutex_init(philo->var->write_mutex, NULL);
	i = 0;
	while (i < var->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, \
			&routine, &philo[i]) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < var->n_philos)
	{
		if (pthread_join(philo[i].thread, NULL) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	pthread_mutex_destroy(philo->var->write_mutex);
	return (EXIT_SUCCESS);
}
//No estoy trabajando con ** en pthread_create. No debería suponer problema.
