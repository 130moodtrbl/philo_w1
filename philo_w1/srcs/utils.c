/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:17:47 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 16:08:36 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	TIME & UTILS
	-	récupère le temps actuel avec gettimeofday()
	-	fait les conversions de microseconds µs en milliseconds 
		(précis mais reste assez faciles à gérer)

*/

/*tv_sec = temps en secondes depuis 01/01/1970*/
/*tv_usec = microsecondes en + */
/*1 sec = 1 000 000 µs (microseconds) */
/*sec * 1000 => milliseconds*/
/*usec / 1000 => milliseconds */
/*retourne le temps actuel écoulé depuis 1170 en milliseconds*/
size_t     current_time(void)
{
      struct timeval    time;
      if (gettimeofday(&time, NULL) == -1)
		write(2, BUG_TOD, 47);
      return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*fonction + précise que usleep pour gérer de mini-pauses dans les stimulations. usleep,est moins précise car le système peut influencer son fonctionnement, si on personnalise nous-même, on peut définir précisément le temps de pauses etc ce qui permet d'éviter certaines latences
	avec helper_usleep, on tourne en boucle avec des petites attentes de 100 microseconds 	(0.0001 secondes, 1e-4) tant que le temps s'écoule bien.
	sans cela (usleep), il y a risque de saturer le CPU, c de la bonne pratique
on fait une sorte de chronomètre pour voir le temps qui s’est écoulé: current - start
*/
int     helper_usleep(size_t milisecs)
{
      size_t  starting_time;

      starting_time = current_time();
      while ((current_time() - starting_time) < milisecs)
            usleep(100);
      return (0);
}

size_t	utils_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (-1);
	while (str[len])
		len++;
	return (len);
}

/*error msg*/
void	error_msg(const char *msg)
{
	if (msg)
		write(2, msg, utils_strlen(msg)); // ou manuellement : write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
