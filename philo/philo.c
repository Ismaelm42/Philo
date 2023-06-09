/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:13 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/27 11:07:05 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_var	*struct_init_var(int argc, char **argv)
{
	t_var	*var;

	var = (t_var *) malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	var->flag = 1;
	var->eat_counter = 0;
	var->nbr_philos = long_atoi(argv[1], &var->flag);
	if (var->nbr_philos > 200 || var->nbr_philos < 0)
		var->nbr_philos = 200;
	var->time_to_death = long_atoi(argv[2], &var->flag);
	var->time_to_eat = long_atoi(argv[3], &var->flag);
	var->time_to_sleep = long_atoi(argv[4], &var->flag);
	var->nbr_eat = -1;
	if (argc > 5)
		var->nbr_eat = long_atoi(argv[5], &var->flag);
	fork_mutex_allocation(var);
	return (var);
}

t_philo	*struct_init_philo(t_var *var)
{
	int			i;
	t_philo		*philo;
	t_time		*life_cycle;

	philo = (t_philo *) malloc(sizeof(t_philo) * var->nbr_philos);
	if (philo == NULL)
		return (NULL);
	life_cycle = (t_time *) malloc(sizeof(t_philo) * var->nbr_philos);
	if (life_cycle == NULL)
		return (free(var), NULL);
	i = 0;
	while (i < var->nbr_philos)
	{
		philo[i].philo = i + 1;
		philo[i].life_cycle = &life_cycle[i];
		philo[i].eat_marker = 0;
		philo[i].var = var;
		philo[i].next_philo = philo[i].philo;
		if (philo[i].philo == philo->var->nbr_philos)
			philo[i].next_philo = 0;
		i++;
	}
	return (philo);
}

int	thread_init(t_philo *philo)
{
	pthread_t	tracker;
	int			i;

	if (pthread_mutex_init(&philo->var->mutex, NULL) == -1 || \
	pthread_mutex_init(&philo->var->counter_mutex, NULL) == -1 || \
	pthread_mutex_init(&philo->var->flag_mutex, NULL) == -1)
		return (4);
	if (pthread_create(&tracker, NULL, &tracker_routine, philo) == -1)
		return (5);
	gettimeofday(&philo->var->time.t_start, NULL);
	i = 0;
	while (i < philo->var->nbr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, \
			&thread_routine, &philo[i]) == -1)
			return (5);
		i++;
	}
	return (thread_join(philo, tracker));
}

int	thread_join(t_philo *philo, pthread_t tracker)
{
	int	i;

	i = 0;
	while (i < philo->var->nbr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) == -1)
			return (6);
		i++;
	}
	if (pthread_join(tracker, NULL) == -1)
		return (6);
	i = 0;
	while (i < philo->var->nbr_philos)
	{
		pthread_mutex_destroy(&philo->var->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->var->mutex);
	pthread_mutex_destroy(&philo->var->counter_mutex);
	pthread_mutex_destroy(&philo->var->flag_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	*var;
	t_philo	*philo;
	int		id;

	if (argc < 5)
		return (error(1));
	var = struct_init_var(argc, argv);
	if (var == NULL)
		return (error(2));
	if (var->flag == -1 || var->nbr_philos == 0)
		return (deallocate(0, var), error(3));
	philo = struct_init_philo(var);
	if (philo == NULL)
		return (deallocate(philo, NULL), error(2));
	id = thread_init(philo);
	if (id != 0)
		return (deallocate(philo, 0), error(id));
	deallocate(philo, NULL);
	return (0);
}
