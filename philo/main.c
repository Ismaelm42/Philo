#include "philo.h"

int	main(int argc, char **argv)
{
	t_var	*var;
	t_philo	*philo;

	if (argc < 5)
		return (print(ARG_ERRN, 2, EXIT_FAILURE));
	var = struct_init_var(argc, argv);
	if (var->flag == -1 || var->n_philos == 0)
		return (free(var), print(ARG_ERR, STDERR_FILENO, EXIT_FAILURE));
	philo = struct_init_philo(var);
	if (thread_init(philo, var) != 0)
		return (ft_free(philo), print(THRD_ERR, STDERR_FILENO, EXIT_FAILURE));
	return (0);
}
