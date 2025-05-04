/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:01:51 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 15:18:58 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	retourne -1 comme dans le man pour faciliter le error handling
	• atoi: pour av into int
	• check_for_dig: différents retours pour tester l’input
*/

long	utils_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (sign * res);
}

int	check_for_dig(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf(WNBARGS));
	if (utils_atoi(av[1]) <= 0 || utils_atoi(av[1]) > 200)
		return (printf(INP));
	if (utils_atoi(av[2]) <= 0 || check_for_dig(av[2]))
		return (printf(ITTD));
	if (utils_atoi(av[3]) <= 0 || check_for_dig(av[3]))
		return (printf(ITTE));
	if (utils_atoi(av[4]) <= 0 || check_for_dig(av[4]))
		return (printf(ITTS));
	if (ac == 6 && (utils_atoi(av[5]) <= 0 || check_for_dig(av[5])))
		return (printf(INB));
	return (0);
}
