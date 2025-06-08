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

// Función para cleanup en caso de error durante inicialización
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

// Función para cleanup completo al final del programa
void	cleanup_table(t_table *table)
{
	int	i;

	if (!table)
		return;
	
	// Destruir todos los mutex de los forks
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
	
	// Destruir otros mutex
	pthread_mutex_destroy(&table->waiter);
	pthread_mutex_destroy(&table->write_lock);
	
	// Liberar arrays y estructura principal
	if (table->philos)
		free(table->philos);
	free(table);
}

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
		table->philos[i].time_last_meal = 0;
		if (i == table->nphilos - 1)
			table->philos[i].l_fork = &table->forks[0];
		else
			table->philos[i].l_fork = &table->forks[i + 1];
		table->philos[i].table = table;
		i++;
	}
}

// Inicializacion mesa
t_table	*init_table(char **av, int ac)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
		
	// Inicializar punteros a NULL para cleanup seguro
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
		
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->nphilos);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nphilos);
	
	if (!table->philos || !table->forks)
	{
		cleanup_partial_table(table, 0);
		return (NULL);
	}
	
	// Inicializar mutex de los forks
	i = 0;
	while (i < table->nphilos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			cleanup_partial_table(table, i); // Cleanup de los mutex ya inicializados
			return (NULL);
		}
		i++;
	}
	
	// Inicializar otros mutex
	if (pthread_mutex_init(&(table->waiter), NULL) != 0)
	{
		cleanup_partial_table(table, table->nphilos);
		return (NULL);
	}
	
	if (pthread_mutex_init(&(table->write_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&table->waiter);
		cleanup_partial_table(table, table->nphilos);
		return (NULL);
	}
	
	init_philos(table);
	return (table);
}