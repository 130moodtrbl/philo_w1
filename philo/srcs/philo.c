/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:14:04 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 15:34:43 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{	
	t_table		table;
	t_philos	philos[200];

	if (check_args(ac, av))
		return (1);
	philos->table = &table;
	printf("\e[1;37m------  --- ----------------\n");
	printf(" TIME    ID     ACTION  \n");
	printf("------  --- ---------------- \e[0m\n");
	init_set_table(philos, &table, av);
	init_seat_philos(&table, philos, av);
	dinner_begin(&table, philos, av);
	dinner_over(&table, philos, av);
	return (0);
}
