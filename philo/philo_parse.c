/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:13 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 11:58:26 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_var	*struct_init_var(int argc, char **argv)
{
	int		i;
	t_var	*var;

	var = (t_var *) malloc(sizeof(t_var));
	var->write_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	var->flag = 1;
	var->n_philos = long_atoi(argv[1], &var->flag);
	if (var->n_philos > 200)
		var->n_philos = 200;
	var->t_death = long_atoi(argv[2], &var->flag);
	var->t_eat = long_atoi(argv[3], &var->flag);
	var->t_sleep = long_atoi(argv[4], &var->flag);
	var->n_eat = -1;
	if (argc > 5)
		var->n_eat = long_atoi(argv[5], &var->flag);
	var->fork_mutex = (pthread_mutex_t *) \
		malloc(sizeof(pthread_mutex_t) * var->n_philos);
	i = 0;
	while (i < var->n_philos)
	{
		pthread_mutex_init(&var->fork_mutex[i], NULL);
		i++;
	}
	return (var);
}

/*
	Al cerrar el programa hay que hacer while
	con pthread_mutex_destroy para eliminarlos.
*/
t_philo	*struct_init_philo(t_var *var)
{
	int		i;
	t_philo	*philo;
	t_time	*life_time;

	philo = (t_philo *) malloc(sizeof(t_philo) * var->n_philos);
	life_time = (t_time *) malloc(sizeof(t_philo) * var->n_philos);
	i = 0;
	while (i < var->n_philos)
	{
		philo[i].n_philo = i + 1;
		philo[i].n_fork = i + 1;
		philo[i].life_time = &life_time[i];
		philo[i].var = var;
		i++;
	}
	return (philo);
}
//times_philos_eat devuelve -1 cuando no se ha introducido ningún valor.
