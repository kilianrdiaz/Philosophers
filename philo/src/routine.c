/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:31:22 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/21 15:11:00 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

	if (philo->id % 2 == 0)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
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

static void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->waiter);
	philo->time_last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->waiter);
	ft_usleep(philo->table->time_to_eat);
}

static void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	print_status(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo || !philo->table)
		return (NULL);
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
		ft_usleep(philo->table->time_to_eat / 2);
	while (should_continue(philo))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
