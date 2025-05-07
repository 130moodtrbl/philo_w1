/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:17:28 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 15:35:32 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	dinner_begin(t_table *table, t_philos *philos, char **av)
{
	size_t	i;

	(void) av;
	init_starting_time(table, philos);
	i = 0;
	while (i < table->philos->nb_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				routine, &table->philos[i]) != 0)
			error_msg(ERR_CREATE_THREAD);
		i++;
	}
	if (pthread_create(&table->table, NULL, state_checker, table->philos) != 0)
		error_msg(ERR_CREATE_THREAD);
	i = 0;
	while (i < table->philos->nb_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->table, NULL);
}

void	dinner_over(t_table *table, t_philos *philos, char **av)
{
	size_t	i;

	i = 0;
	(void) av;
	pthread_mutex_destroy(&table->mutex);
	pthread_mutex_destroy(table->lock_is_dead);
	free(table->lock_is_dead);
	pthread_mutex_destroy(table->lock_has_eaten);
	free(table->lock_has_eaten);
	while (i < table->philos->nb_of_philos)
	{
		pthread_mutex_destroy(philos[i].lock_last_meal);
		free(philos[i].lock_last_meal);
		pthread_mutex_destroy(philos[i].lock_has_eaten);
		free(philos[i].lock_has_eaten);
		pthread_mutex_destroy(philos[i].lock_meal_count);
		free(philos[i].lock_meal_count);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	print_state(t_philos *philo, char *state)
{
	pthread_mutex_lock(&philo->table->mutex);
	pthread_mutex_lock(philo->table->lock_is_dead);
	if (!*philo->is_dead || utils_strcmp(state, "died") == 0)
	{
		printf("\033[0;38;5;245m%lu\e[0m ", current_time() - philo->table->starting_time);
		if (utils_strcmp(state, "FORK") == 0)
			printf(STATE_FORK, philo->philo_seat);
		else if (utils_strcmp(state, "EAT") == 0)
			printf(STATE_EAT, philo->philo_seat);
		else if (utils_strcmp(state, "SLEEP") == 0)
			printf(STATE_SLEEP, philo->philo_seat);
		else if (utils_strcmp(state, "THINK") == 0)
			printf(STATE_THINK, philo->philo_seat);
		else if (utils_strcmp(state, "died") == 0)
			printf(STATE_DIE, philo->philo_seat);
	}
	pthread_mutex_unlock(philo->table->lock_is_dead);
	pthread_mutex_unlock(&philo->table->mutex);
}
