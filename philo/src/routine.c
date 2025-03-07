/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:31:22 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/04 14:01:06 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// Liberar tenedores
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

// Coger tenedores
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->waiter);
	pthread_mutex_unlock(&philo->table->waiter);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	usleep(philo->table->time_to_eat);
	release_forks(philo);
}

// Bucle de acciones de los filósofos
void	routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->table->dead)
	{
		printf("");
		//Eat
		take_forks(philo);
		//Sleep
		usleep(philo->table->time_to_sleep);
		//Think
		printf("Thinking...");
		//Repeat
	}
}