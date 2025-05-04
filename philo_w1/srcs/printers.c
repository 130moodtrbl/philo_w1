/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:41:01 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 19:48:00 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_state(t_philos *philo, char *state)
{
	pthread_mutex_lock(&philo->table->mutex);
	pthread_mutex_lock(philo->table->lock_is_dead);
	if (!*philo->is_dead)
	{
		printf("%lu ", current_time() - philo->table->starting_time);
		if (utils_strcmp(state, "FORK") == 0)
			printf("%03d has taken a fork\n", philo->philo_seat);
		else if (utils_strcmp(state, "EAT") == 0)
			printf("%03d is eating\n", philo->philo_seat);
		else if (utils_strcmp(state, "SLEEP") == 0)
			printf("%03d is sleeping\n", philo->philo_seat);
		else if (utils_strcmp(state, "THINK") == 0)
			printf("%03d is thinking\n", philo->philo_seat);
		else if (utils_strcmp(state, "DEAD") == 0)
			printf("%03d died\n", philo->philo_seat);		
	}
	pthread_mutex_unlock(philo->table->lock_is_dead);
	pthread_mutex_unlock(&philo->table->mutex);
}

int utils_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return(s1[i] - s2[i]);
}