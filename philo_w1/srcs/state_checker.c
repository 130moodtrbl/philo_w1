/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:09:56 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 19:08:16 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	Supervisor/state_checker
		Is philo alive? yes = 0, no = 1
		Has philo starved? yes = 0, no = 1, si le last_meal est = grand que ttd

*/

/*vérifie si un philosophe est mort, si oui → 1 sinon, 0*/
int	is_philo_still_alive(t_philos *philo)
{
	pthread_mutex_lock(philo->table->lock_is_dead); /*lock pour acceder a philo is_dead*/
	if (*philo->is_dead) /*death flag*/
	{
		pthread_mutex_unlock(philo->table->lock_is_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->table->lock_is_dead);
	return (0);
}

/*philo_has_starved, on vérifie si le temps actuel - le dernier repas est > au temps en av maximum avant de mourir*/
int	is_philo_starved(t_philos *philo)
{
	pthread_mutex_lock(philo->lock_last_meal); /*pr que chaque philo ait bien sa donnée et qu'il ne soit pas changé pendant sa maj*/
	if (current_time() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->lock_last_meal);
		return (1);
	}
	pthread_mutex_unlock(philo->lock_last_meal);
	return (0);
}

/*philo_has_starved, on vérifie si le temps actuel - le dernier repas est > au temps en av maximum avant de mourir*/
int	is_philo_dead(t_philos *philo)
{
	size_t	i;

	i = 0;
	while (i < philo[0].nb_of_philos)
	{
		if (is_philo_starved(&philo[i]))
		{
			pthread_mutex_lock(philo->table->lock_is_dead);
			if (!*philo->is_dead)
			{
				pthread_mutex_unlock(philo->table->lock_is_dead);
				print_state(philo, "DEAD");  /*evite deadlocks*/
				pthread_mutex_lock(philo->table->lock_is_dead);
				*philo->is_dead = 1;
				pthread_mutex_unlock(philo->table->lock_is_dead);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_philo_full(t_philos *philo)
{
	size_t	i;
	int		meal_counter;

	i = 0;
	meal_counter = 0;
	while (i < philo[0].nb_of_philos)
	{
		pthread_mutex_lock(philo->table->lock_has_eaten);
		if (philo[i].has_eaten >= philo->table->total_meal
			&& philo->table->total_meal != -1)
			meal_counter++;
		pthread_mutex_unlock(philo->table->lock_has_eaten);
		i++;
	}
	if (meal_counter == (int)philo[0].nb_of_philos) /*a simplifier*/
	{
		pthread_mutex_lock(philo->table->lock_is_dead);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->table->lock_is_dead);
		return (1);
	}
	return (0);
}

void	*state_checker(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
		if (is_philo_dead(philos) || is_philo_full(philos))
			break ;
	return (arg);
}