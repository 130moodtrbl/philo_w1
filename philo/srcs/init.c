/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:34:16 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 15:37:18 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_invited_philos(t_philos *philos, char **av)
{
	if (!philos || !philos->table)
		error_msg(BUG_UNIPHIL);
	philos->nb_of_philos = utils_atoi(av[1]);
	philos->lock_last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos->lock_last_meal)
		return ;
	philos->lock_has_eaten = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos->lock_has_eaten)
		return ;
	philos->lock_meal_count = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t));
	if (!philos->lock_has_eaten)
		return ;
	pthread_mutex_init(philos->lock_last_meal, NULL);
	pthread_mutex_init(philos->lock_has_eaten, NULL);
	pthread_mutex_init(philos->lock_meal_count, NULL);
	philos->last_meal = current_time();
	philos->is_dead = &philos->table->death_check;
	philos->time_to_die = utils_atoi(av[2]);
	philos->time_to_eat = utils_atoi(av[3]);
	philos->time_to_sleep = utils_atoi(av[4]);
	philos->is_sleeping = 0;
	philos->has_eaten = 0;
}

void	init_seat_philos(t_table *table, t_philos *philos, char **av)
{
	size_t	i;
	int		nb_philos;

	i = 0;
	nb_philos = utils_atoi(av[1]);
	while (i < (size_t)nb_philos)
	{
		philos[i].philo_seat = i + 1;
		philos[i].table = table;
		init_invited_philos(&philos[i], av);
		i++;
	}
}

void	init_set_table(t_philos *philos, t_table *table, char **av)
{
	size_t	i;

	table->philos = philos;
	pthread_mutex_init(&table->mutex, NULL);
	table->lock_is_dead = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->lock_is_dead, NULL);
	table->lock_has_eaten = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->lock_has_eaten, NULL);
	i = 0;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* utils_atoi(av[1]));
	while (i < (size_t)utils_atoi(av[1]))
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->death_check = 0;
	if (av[5])
		table->total_meal = utils_atoi(av[5]);
	else
		table->total_meal = -1;
}

void	init_starting_time(t_table *table, t_philos *philos)
{
	size_t	i;

	i = 0;
	table->starting_time = current_time();
	while (i < table->philos->nb_of_philos)
	{
		philos[i].last_meal = table->starting_time;
		i++;
	}
}
