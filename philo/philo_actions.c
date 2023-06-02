/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:43:40 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 14:50:35 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	//bloquear mutex tenedor x && x + 1;
	//imprimir estado philo en ms;
	//usleep philo->var->t_eat;
	//desbloquear mutex tenedor x && x + 1;
}

void	sleeping(t_philo *philo)
{
	// imprimir estado philo en ms;
	// usleep philo->var->t_sleep;
}

void	thinking(t_philo *philo)
{
	// imprimir estado philo en ms;
	// usleep (¿tiempo?);
}
