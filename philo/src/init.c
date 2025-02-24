/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:38:42 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/02/24 18:16:50 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nphilos)
	{
		table->philos[i].id = i;
		table->philos[i].meals_eaten = 0;
		table->philos[i].r_fork = &table->forks[i];
		if (i == table->nphilos - 1)
			table->philos[i].l_fork = &table->forks[0];
		else
			table->philos[i].l_fork = &table->forks[i + 1];
		table->philos[i].table = table;
		i++;
	}
}

void	init_table(t_table *table, char **av, int ac)
{
	int	i;

	table->nphilosophers = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
    	table->nmeals = ft_atol(av[5]);
	else
		table->nmeals = -1;
	table->start_time = get_time_ms();
	table->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * table->nphilos);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nphilos);
	if (!table->philos || !table->forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < table->nphilos)
		pthread_mutex_init(&table->forks[i++], NULL);
	init_philos(table);
}
