/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:18:44 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 15:27:39 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	lonely_philo(t_philos *philo)
{
	helper_usleep(1);
	if (philo->nb_of_philos == 1)
	{
		pthread_mutex_lock(&philo->table->forks[0]);
		print_state(philo, "FORK");
		while (!*philo->is_dead)
			helper_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->table->lock_is_dead);
		return (1);
	}
	return (0);
}

void	philo_eating(t_philos *philo)
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

	get_forks(philo, &right_fork, &left_fork);
	lock_forks(philo, right_fork, left_fork);
	print_state(philo, "EAT");
	pthread_mutex_lock(philo->lock_last_meal);
	philo->last_meal = current_time();
	pthread_mutex_lock(philo->lock_has_eaten);
	philo->has_eaten++;
	pthread_mutex_unlock(philo->lock_has_eaten);
	pthread_mutex_unlock(philo->lock_last_meal);
	helper_usleep(philo->time_to_eat);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

void	philo_sleeping(t_philos *philo)
{
	print_state(philo, "SLEEP");
	helper_usleep(philo->time_to_sleep);
}

void	philo_thinking(t_philos *philo)
{
	print_state(philo, "THINK");
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->philo_seat % 2 == 0)
		helper_usleep(10);
	if (lonely_philo(philo))
		return (NULL);
	philo->last_meal = current_time();
	while (!*philo->is_dead)
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}
