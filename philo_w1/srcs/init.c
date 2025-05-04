/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:25:35 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 19:41:03 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*prep simulation*/
void	init_invited_philos(t_philos *philos, char **av)
{
	if (!philos || !philos->table)
		error_msg(BUG_UNIPHIL);
	philos->nb_of_philos = utils_atoi(av[1]);
	philos->lock_last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos->lock_last_meal)
		return ; /*🔧 fonction gestion d’erreur quitte propre, exit?*/
	philos->lock_has_eaten = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philos->lock_has_eaten)
		return ; /*🔧 fonction gestion d’erreur quitte propre, exit?*/
	/*init les mutexes 🔒*/
	pthread_mutex_init(philos->lock_last_meal, NULL);
	pthread_mutex_init(philos->lock_has_eaten, NULL);
	/*init le dernier repas*/
	philos->last_meal = current_time();
	/*va chercher dans table le flag de la mort*/
	philos->is_dead = &philos->table->death_check;
	/*init*/
	philos->time_to_die = utils_atoi(av[2]);
	philos->time_to_eat = utils_atoi(av[3]);
	philos->time_to_sleep = utils_atoi(av[4]);
	philos->is_sleeping = 0;
	philos->has_eaten = 0;
}

/*gère l'entrée, attribue seat dans le tableau puis passe au suivant → dessin videur boite*/
void	init_seat_philos(t_table *table, t_philos *philos, char **av)
{
	size_t	i;
	int		nb_philos;

	i = 0;
	nb_philos = utils_atoi(av[1]);
	while (i < (size_t)nb_philos)
	{
		philos[i].philo_seat = i + 1; /*commence à 1, on attribue un siège à chaque philo*/
		philos[i].table = table; /*associe chak philo à la table & ressources (sayer assis)*/
		init_invited_philos(&philos[i], av); /*invités installés, on init tout*/ 
		i++;
	}
}

/*set_table → mettre la table, mettre en en place la simulation*/
void	init_set_table(t_philos *philos, t_table *table, char **av)
{
	size_t	i;

	table->philos = philos; /*on declare bien que philos dans table = philos*/
	pthread_mutex_init(&table->mutex, NULL); /*init mutex general, SANS LE MALLOC?*/
	table->lock_is_dead = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->lock_is_dead, NULL);
	table->lock_has_eaten = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->lock_has_eaten, NULL);		
	i = 0;
	table->forks = (pthread_mutex_t *)
	malloc(sizeof(pthread_mutex_t) * utils_atoi(av[1]));
		/*🔧 test malloc? 25 lignes fonction gestion d’erreur quitte propre, exit?*/
	while (i < (size_t)utils_atoi(av[1])) /*init 1 mutex pour chaque fork, on utilise un tableau*/
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->death_check = 0;  /*0 psq repas pas encore commence, donc tt le monde alive*/
	if (av[5])
		table->total_meal = utils_atoi(av[5]);
	else
		table->total_meal = -1;  /*sinon illimité juska ca crash*/
}

