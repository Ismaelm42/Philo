/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:59:04 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/06/02 11:59:05 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_var	*var;
	t_philo	*philo;

	if (argc < 5)
		return (error(ARG_ERRN));
	var = struct_init_var(argc, argv);
	if (var->flag == -1 || var->n_philos == 0)
		return (free(var), error(ARG_ERR));
	philo = struct_init_philo(var);
	if (thread_init(philo, var) != 0)
		return (deallocate(philo), error(THRD_ERR));
	return (0);
}
