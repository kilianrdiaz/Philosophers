/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:38:42 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/04 14:01:13 by kroyo-di         ###   ########.fr       */
/*   Updated: 2025/03/14 13:52:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_philo(t_table table, int id)
{
	table->philos[i - 1].id = id;
}

#include "../inc/philosophers.h"

// Inicializacion filosofos
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
	table->philos->table = table;
}

// Inicializacion mesa
void	init_table(t_table *table, char **av, int ac)
{
	int	i;

	table->nphilosophers = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->dead = 0;
	if (ac == 6)
    	table->nmeals = ft_atol(av[5]);
	else
		table->nmeals = -1;
	table->start_time = get_time_ms();
	table->philos = (t_philo *)malloc(sizeof(t_philo * table->nphilos));
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nphilos);
	if (!table->philos || !table->forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < table->nphilos)
		pthread_mutex_init(&table->forks[i++], NULL);
	pthread_mutex_init(&table->waiter, NULL);
	pthread_mutex_init(&table->writing, NULL);
	init_philos(table);
}
