/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:57:01 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/21 15:02:50 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	stop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nphilos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	if (table->nphilos > 1)
		pthread_join(table->monitor_thread, NULL);
}

static int	start(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->nphilos)
	{
		table->philos[i].time_last_meal = table->start_time;
		i++;
	}
	i = 0;
	while (i < table->nphilos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, routine,
				&table->philos[i]) != 0)
			return (1);
		i++;
	}
	if (table->nphilos > 1)
	{
		if (pthread_create(&table->monitor_thread, NULL, monitor, table) != 0)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac == 5 || ac == 6)
	{
		check_args(ac, av);
		table = init_table(av, ac);
		if (!table)
			return (EXIT_FAILURE);
		if (start(table) == 1)
			return (EXIT_FAILURE);
		stop(table);
		cleanup_table(table);
		return (EXIT_SUCCESS);
	}
	else
		print_valid_args();
	return (EXIT_FAILURE);
}
