/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:38:42 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/11 21:08:18 by kroyo-di         ###   ########.fr       */
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
void	init_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->nphilos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].time_last_meal = 0;
		philos[i].table = table;
		philos[i].pid = fork();
		if (pid < 0)
        {
			printf("Error while executing : fork()\n");
			exit(1);
		}
		else if (philos[i].pid == 0)
		{
			// Proceso hijo - ejecutar rutina del filósofo
			routine(&philos[i]);
			exit(0);
		}
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
	table->forks = (sem_t *)malloc(sizeof(sem_t) * table->nphilos);
	
	if (!table->philos || !table->forks)
	{
		cleanup_partial_table(table, 0);
		return (NULL);
	}
	
	init_philos(table);
	return (table);
}
