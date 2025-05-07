/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:19:40 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 16:36:33 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_has_starved(t_philos *philo)
{
	long	curr;

	curr = current_time();
	pthread_mutex_lock(philo->lock_last_meal);
	if (curr - philo->last_meal >= philo->time_to_die)
	{
		pthread_mutex_unlock(philo->lock_last_meal);
		return (1);
	}
	pthread_mutex_unlock(philo->lock_last_meal);
	return (0);
}

int	philo_has_died(t_philos *philo)
{
	pthread_mutex_lock(philo->table->lock_is_dead);
	if (!*philo->is_dead)
	{
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->table->lock_is_dead);
		print_state(philo, "died");
		return (1);
	}
	pthread_mutex_unlock(philo->table->lock_is_dead);
	return (0);
}

int	check_any_philo_dead(t_philos *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].nb_of_philos)
	{
		if (philo_has_starved(&philos[i]))
			return (philo_has_died(&philos[i]));
		i++;
	}
	return (0);
}

int	are_all_philos_full(t_philos *philos)
{
	size_t	i;
	int		meal_counter;

	i = 0;
	meal_counter = 0;
	while (i < philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[i].lock_meal_count);
		if (philos[i].has_eaten >= philos[0].table->total_meal
			&& philos[0].table->total_meal != -1)
			meal_counter++;
		pthread_mutex_unlock(philos[i].lock_meal_count);
		i++;
	}
	if (meal_counter == (int)philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[0].table->lock_is_dead);
		*philos[0].is_dead = 1;
		pthread_mutex_unlock(philos[0].table->lock_is_dead);
		printf(PHILOS_FULL, philos->table->total_meal);
		return (1);
	}
	return (0);
}

void	*state_checker(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		if (check_any_philo_dead(philos) || are_all_philos_full(philos))
			break ;
		helper_usleep(10);
	}
	return (NULL);
}
