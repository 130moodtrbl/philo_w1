#include "../inc/philo.h"

int	lonely_philo(t_philos *philo)
{
	helper_usleep(1);
	if (philo->nb_of_philos == 1)
	{
		print_state(philo, "FORK");
		helper_usleep(philo->time_to_die);
		print_state(philo, "DEAD");
		pthread_mutex_lock(philo->table->lock_is_dead);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->table->lock_is_dead);
		return (0);
	}
	return (0);
}