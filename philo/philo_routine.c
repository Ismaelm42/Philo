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

//puedo usar un mutex para routine pero para tracker, que comparte variables
//con otros hilos, tengo que usar otros mutex para esas variables.
//usleep protege get_time para que los tiempos no sean incongruentes.
//Imperativo dejarlo.
//Ya he comprobado muchas veces que si lo quito se va todo a la puta.

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo % 2 == 0)
		add_delay(philo, philo->var->time.t_start);
	//He cambiado el '% 2 != 0' a '== 0'
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
