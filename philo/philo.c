/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:13 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/08 14:15:27 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_var	*struct_init_var(int argc, char **argv)
{
	int		i;
	t_var	*var;

	var = (t_var *) malloc(sizeof(t_var));
	var->write_mtx = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
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
	var->fork_mtx = (pthread_mutex_t *) \
		malloc(sizeof(pthread_mutex_t) * var->n_philos);
	i = 0;
	while (i < var->n_philos)
	{
		pthread_mutex_init(&var->fork_mtx[i], NULL);
		i++;
	}
	return (var);
}

//Al cerrar el programa hay que hacer while con
//pthread_mtx_destroy para eliminarlos.

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
		philo[i].eat_counter = 0;
		philo[i].var = var;
		philo[i].unlock_left = 0;
		philo[i].unlock_right = 0;
		i++;
	}
	return (philo);
}

//times_philos_eat devuelve -1 cuando no se ha introducido ningún valor.

int	thread_init(t_philo *philo)
{
	pthread_t			tracker;
	int					i;

	gettimeofday(&philo->var->time.t_start, NULL);
	pthread_mutex_init(philo->var->write_mtx, NULL);
	pthread_create(&tracker, NULL, &tracker_routine, philo);
	i = 0;
	while (i < philo->var->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, \
			&thread_routine, &philo[i]) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (thread_join(philo, tracker));
}

int	thread_join(t_philo *philo, pthread_t tracker)
{
	int	i;

	i = 0;
	while (i < philo->var->n_philos)
	{
		if (pthread_join(philo[i].thread, NULL) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(tracker, NULL) == -1)
		return (EXIT_FAILURE);
	i = 0;
	while (i < philo->var->n_philos)
	{
		pthread_mutex_destroy(&philo->var->fork_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(philo->var->write_mtx);
	return (EXIT_SUCCESS);
}
//pthread_join(tracker...) debe estar al final, si no da resultados raros.

int	main(int argc, char **argv)
{
	t_var	*var;
	t_philo	*philo;

	atexit(ft_leaks);
	if (argc < 5)
		return (error(ARG_ERRN));
	var = struct_init_var(argc, argv);
	if (var->flag == -1 || var->n_philos == 0)
		return (deallocate(NULL, var), error(ARG_ERR));
	philo = struct_init_philo(var);
	if (thread_init(philo) != 0)
		return (deallocate(philo, NULL), error(THRD_ERR));
	deallocate(philo, NULL);
	return (0);
}
