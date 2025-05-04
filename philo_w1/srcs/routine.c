/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:21:59 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 19:49:52 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eating(t_philos *philo)
{
	pthread_mutex_t *fork1; /*celle mm chiffre que le philo, droite*/
	pthread_mutex_t *fork2; /*gauche*/

	fork1 = &philo->table->forks[(philo->philo_seat) % philo->nb_of_philos];
	fork2 = &philo->table->forks[(philo->philo_seat - 1) % philo->nb_of_philos];
	if (philo->philo_seat % 2 == 0) /*si le philo est pair*/
	{
		fork2 = fork1;
		fork1 = &philo->table->forks[(philo->philo_seat - 1)];
	}
	pthread_mutex_lock(fork1);
	print_state(philo, "FORK");
	pthread_mutex_lock(fork2);
	print_state(philo, "FORK");
	print_state(philo, "EAT");
	pthread_mutex_lock(philo->lock_last_meal); /*lock le dernier repas pr ke seul lui le mette a jour*/
	philo->last_meal = current_time();
	pthread_mutex_lock(philo->lock_has_eaten);
	philo->has_eaten++;
	pthread_mutex_unlock(philo->table->lock_has_eaten);
	pthread_mutex_unlock(philo->lock_last_meal);
	helper_usleep(philo->time_to_eat); /*cb de temps ca doit durer*/
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

void *routine(void *arg)
{
	t_philos	*philo;
	philo = (t_philos *)arg;
	if (philo->philo_seat % 2 == 0)
		helper_usleep(10);
	if (lonely_philo(philo))
		return (arg);
	philo->last_meal = current_time();
	while(!*philo->is_dead)
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}