/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:07 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/27 11:20:27 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int	error(int id)
{
	if (id == 1)
		write (2, ARG_ERRN, ft_strlen(ARG_ERRN));
	else if (id == 2)
		write (2, MEM_ERR, ft_strlen(MEM_ERR));
	else if (id == 3)
		write (2, ARG_ERR, ft_strlen(ARG_ERR));
	else if (id == 4)
		write (2, MTX_ERR, ft_strlen(MTX_ERR));
	else if (id == 5)
		write (2, THRD_INIT_ERR, ft_strlen(THRD_INIT_ERR));
	else if (id == 6)
		write (2, THRD_JOIN_ERR, ft_strlen (THRD_JOIN_ERR));
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
	if (sum > 100000 || sum < 0)
		sum = 100000;
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
		if (pthread_mutex_init(&var->fork_mutex[i], NULL) == -1)
			return (NULL);
		i++;
	}
	return (var);
}
