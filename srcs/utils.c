/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:14:39 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 16:08:35 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, BUG_TOD, 47);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	helper_usleep(size_t milisecs)
{
	size_t	starting_time;

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

void	error_msg(const char *msg)
{
	if (msg)
		write(2, msg, utils_strlen(msg));
	exit(EXIT_FAILURE);
}

int	utils_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
