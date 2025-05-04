/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:51:18 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 19:44:46 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{	
	t_table	table;
	t_philos	philos[200];

	if (check_args(ac, av))
		return (1); /*exit*/
	philos->table = &table;
	init_set_table(philos, &table, av);
	init_seat_philos(&table, philos, av);
	dinner_begin(&table, philos, av);
	dinner_over(&table, philos, av);
	return (0);
}
