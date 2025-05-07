/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:26:07 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 15:28:00 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	get_forks(t_philos *philo, pthread_mutex_t **right_fork,
	pthread_mutex_t **left_fork)
{
	*right_fork = &philo->table->forks[(philo->philo_seat)
		% philo->nb_of_philos];
	*left_fork = &philo->table->forks[(philo->philo_seat - 1)
		% philo->nb_of_philos];
}

void	lock_forks(t_philos *philo, pthread_mutex_t *right_fork,
	pthread_mutex_t *left_fork)
{
	if (philo->philo_seat % 2 == 0)
	{
		pthread_mutex_lock(right_fork);
		print_state(philo, "FORK");
		pthread_mutex_lock(left_fork);
		print_state(philo, "FORK");
	}
	else
	{
		pthread_mutex_lock(left_fork);
		print_state(philo, "FORK");
		pthread_mutex_lock(right_fork);
		print_state(philo, "FORK");
	}
}
