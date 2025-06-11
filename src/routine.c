/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:31:22 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/11 21:43:20 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Liberar tenedores
void	release_forks(t_philo *philo)
{
	if (philo->l_fork)
		pthread_mutex_unlock(philo->l_fork);
	if (philo->r_fork)
		pthread_mutex_unlock(philo->r_fork);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	// Prevención de deadlock: orden según ID del filósofo
	if (philo->id % 2 == 0)  // Filósofo par
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else  // Filósofo impar
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}

	// Verificar que los punteros sean válidos antes de hacer lock
	if (!first_fork || !second_fork)
	{
		printf("Error: Invalid fork pointers for philo %d\n", philo->id);
		return ;
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
}

// Función para comer
static void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	
	// Actualizar tiempo de última comida (thread-safe)
	pthread_mutex_lock(&philo->table->waiter);
	philo->time_last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->waiter);
	// Simular tiempo comiendo
	ft_usleep(philo->table->time_to_eat);
}

// Función para dormir y pensar
static void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	print_status(philo, "is thinking");
}

// Bucle de acciones de los filósofos
void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (!philo || !philo->table)
	{
		printf("Error: Invalid philosopher data\n");
		return (NULL);
	}
	if (philo->table->nmeals == 0)
		return (NULL);
	if (philo->table->nphilos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->table->time_to_die);
		print_status(philo, "died");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (should_continue(philo))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
