/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:38:42 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/06 19:57:18 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Inicializacion filosofos
void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nphilos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].r_fork = &table->forks[i];
		table->philos[i].time_last_meal = table->start_time;
		if (i == table->nphilos - 1)
			table->philos[i].l_fork = &table->forks[0];
		else
			table->philos[i].l_fork = &table->forks[i + 1];
		table->philos[i].table = table;
		i++;
	}
	table->philos->table = table;
}

// Inicializacion mesa
t_table	*init_table(char **av, int ac)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
        return (NULL);
	table->nphilos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->nmeals = ft_atol(av[5]);
	else
		table->nmeals = -1;
	table->start_time = get_time_ms();
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->nphilos);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nphilos);
	if (!table->philos || !table->forks)
	{
		if (table->philos)
			free(table->philos);
		if (table->forks)
			free(table->forks);
		return (NULL);
	}
	i = 0;
	while (i < table->nphilos)
	{
		if (pthread_mutex_init(&table->forks[i++], NULL) != 0)
			return (NULL);
	}
	if (pthread_mutex_init(&(table->waiter), NULL) != 0)
		return (NULL);
	init_philos(table);
	printf("Mesa Inicializada\n");
	return (table);
}
