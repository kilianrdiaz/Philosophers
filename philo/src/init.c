/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:38:42 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/25 17:12:06 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	cleanup_partial_table(t_table *table, int forks_initialized)
{
	int	i;

	if (table)
	{
		if (table->forks && forks_initialized > 0)
		{
			i = 0;
			while (i < forks_initialized)
				pthread_mutex_destroy(&table->forks[i++]);
		}
		if (table->forks)
			free(table->forks);
		if (table->philos)
			free(table->philos);
		free(table);
	}
}

void	cleanup_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->forks)
	{
		i = 0;
		while (i < table->nphilos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->waiter);
	pthread_mutex_destroy(&table->write_lock);
	if (table->philos)
		free(table->philos);
	free(table);
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nphilos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			cleanup_partial_table(table, i);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&(table->waiter), NULL) != 0)
	{
		cleanup_partial_table(table, table->nphilos);
		return (0);
	}
	if (pthread_mutex_init(&(table->write_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&table->waiter);
		cleanup_partial_table(table, table->nphilos);
		return (0);
	}
	return (1);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->nphilos);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->nphilos);
	if (!table->philos || !table->forks || !init_mutex(table))
	{
		cleanup_partial_table(table, 0);
		return (0);
	}
	i = -1;
	while (++i < table->nphilos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].r_fork = &table->forks[i];
		table->philos[i].time_last_meal = 0;
		if (i == table->nphilos - 1)
			table->philos[i].l_fork = &table->forks[0];
		else
			table->philos[i].l_fork = &table->forks[i + 1];
		table->philos[i].table = table;
	}
	return (1);
}

t_table	*init_table(char **av, int ac)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philos = NULL;
	table->forks = NULL;
	table->death_flag = 0;
	table->nphilos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->nmeals = ft_atol(av[5]);
	else
		table->nmeals = -1;
	if (table->nphilos == 0 || !table->time_to_die || !table->time_to_eat
		|| !table->time_to_sleep || !table->nmeals)
	{
		free(table);
		print_valid_args();
	}
	if (!init_philos(table))
		return (NULL);
	return (table);
}
