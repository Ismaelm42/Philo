/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:12:07 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/08 13:14:42 by imoro-sa         ###   ########.fr       */
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

void	deallocate(t_philo *philo, t_var *var)
{
	if (philo == NULL)
	{
		free(var->write_mtx);
		free(var->fork_mtx);
		free(var);
	}
	else
	{
		free(philo->var->write_mtx);
		free(philo->var->fork_mtx);
		free(philo->life_time);
		free(philo->var);
		free(philo);
	}
}

//El if añade la condición cuando life_time no ha sido aún inicializado 
//y se toma el tiempo del comienzo del programa como referencia.

void	ft_leaks(void)
{
	system("leaks -q philo");
}
