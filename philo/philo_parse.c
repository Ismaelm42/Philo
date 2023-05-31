#include "philo.h"

t_var	*struct_init_var(int argc, char **argv)
{
	t_var	*var;

	var = (t_var *) malloc(sizeof(t_var));
	var->mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
	var->flag = 1;
	var->n_philos = ctrl_atoi(argv[1], &var->flag);
	var->t_death = ctrl_atoi(argv[2], &var->flag);
	var->t_eat = ctrl_atoi(argv[3], &var->flag);
	var->t_sleep = ctrl_atoi(argv[4], &var->flag);
	var->n_eat = -1;
	if (argc > 5)
		var->n_eat = ctrl_atoi(argv[5], &var->flag);
	return (var);
}

t_philo	*struct_init_philo(t_var *var)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *) malloc(sizeof(t_philo) * var->n_philos);
	i = 0;
	while (i < var->n_philos)
	{
		philo[i].n_philo = i + 1;
		philo[i].n_fork = i + 1;
		philo[i].var = var;
		i++;
	}
	return (philo);
}
//times_philos_eat devuelve -1 cuando no se ha introducido ningún valor.
