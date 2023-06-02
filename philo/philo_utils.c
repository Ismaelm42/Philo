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

int	print(char *str, int fd, int exit)
{
	int	len;

	len = 0;
	while (str[len] != 0)
		len++;
	write(fd, str, len);
	return (exit);
}

long	ctrl_atoi(char *str, int *flag)
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
	if (sum > 200)
		sum = 200;
	return (sum);
}
	//Capado a 1000 filosofos.
	//Si lo mantengo hasta el valor max de un int da segmentation fault.
	//Debería ser un atoi_long en principio.

void	ft_free(t_philo *philo)
{
	free(philo->var);
	free(philo);
}

void	putnbr(long time)
{
	char	c;

	if (time > 9)
	{
		putnbr(time / 10);
		putnbr(time % 10);
	}
	else
	{
		c = time + '0';
		write (1, &c, 1);
	}
}
	//Comprobar el max int?

void	get_time(t_philo *philo)
{
	long	t_sec;
	long	t_usec;
	long	t;

	t_sec = (philo->var->t_end.tv_sec - philo->var->t_start.tv_sec) * 1000;
	t_usec = philo->var->t_end.tv_usec - philo->var->t_start.tv_usec;
	t = t_sec + t_usec;
	putnbr(t);
	print("ms \n", STDOUT_FILENO, EXIT_SUCCESS);
}
