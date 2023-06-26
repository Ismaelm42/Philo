/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:07 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/26 16:34:57 by imoro-sa         ###   ########.fr       */
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
	int		j;
	long	sum;

	i = 0;
	sum = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	j = i;
	while (str[j] >= '0' && str[j] <= '9')
		j++;
	if (str[j] != 0)
		return (*flag = -1, sum);
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	if (sum > 10000 || sum < 0)
		sum = 10000;
	return (sum);
}

void	deallocate(t_philo *philo, t_var *var)
{
	if (philo == NULL)
	{
		free(var->fork_mutex);
		free(var);
	}
	else
	{
		free(philo->var->fork_mutex);
		free(philo->life_cycle);
		free(philo->var);
		free(philo);
	}
}

t_var	*fork_mutex_allocation(t_var *var)
{
	int					i;

	var->fork_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) \
	* var->nbr_philos);
	if (var->fork_mutex == NULL)
	{
		free(var);
		return (NULL);
	}
	i = 0;
	while (i < var->nbr_philos)
	{
		pthread_mutex_init(&var->fork_mutex[i], NULL);/////////
		i++;
	}
	return (var);
}
