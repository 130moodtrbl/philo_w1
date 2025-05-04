/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:57:20 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 18:45:48 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	Meal_handler
		dinner is ready! tout a ete prepare, on peut maintenant passer à la simulation
		dinner is over! free tout, destroy threads

*/

/*dinner_ready → lance le debut de la smiluation. On introduit un thread qui supervise
 puis les threads des philos, a chaque fois en attendant la fin d’une action avant de lancer
 l’autre (pthread_join, évite data races etc, aussi d'où les mutexes)*/

void	dinner_begin(t_table *table, t_philos *philos, char **av)
{
	size_t	i;

	(void) av;
	(void) philos; /*🔧vérifier utilité*/
	i = 0;
	table->starting_time = current_time();

	while (i < table->philos->nb_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]) != 0) /*chacun reçoit sa routine*/
			error_msg(ERR_CREATE_THREAD);
		i++;
	}
	/*check psq pthread_create returns 0 qd successful, si pas 0, error handling*/
	if (pthread_create(&table->table, NULL, state_checker, table->philos) != 0)
		error_msg(ERR_CREATE_THREAD);
	i = 0;
	while (i < table->philos->nb_of_philos)  /*on attend que tous les philos finissent leur routine, puis le supervisor*/
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->table, NULL);
}

/*dinner_over → destroy tout, free tout, propre*/
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
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}
