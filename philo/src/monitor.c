/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:40:38 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/21 15:12:14 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_continue(t_philo *philo)
{
	int	continue_sim;

	pthread_mutex_lock(&philo->table->waiter);
	if (philo->table->death_flag)
		continue_sim = 0;
	else if (philo->table->nmeals != -1
		&& philo->meals_eaten >= philo->table->nmeals)
		continue_sim = 0;
	else
		continue_sim = 1;
	pthread_mutex_unlock(&philo->table->waiter);
	return (continue_sim);
}

static int	check_death(t_table *table)
{
	int			i;
	long		current_time;

	i = -1;
	current_time = get_time_ms();
	while (++i < table->nphilos)
	{
		pthread_mutex_lock(&table->waiter);
		if (table->death_flag)
		{
			pthread_mutex_unlock(&table->waiter);
			return (1);
		}
		if ((current_time - table->philos[i].time_last_meal)
			> table->time_to_die)
		{
			table->death_flag = 1;
			pthread_mutex_unlock(&table->waiter);
			print_status(&table->philos[i], "died");
			return (1);
		}
		else
			pthread_mutex_unlock(&table->waiter);
	}
	return (table->death_flag);
}

static int	check_all_ate(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->nmeals == -1)
		return (0);
	if (table->death_flag)
		return (1);
	i = 0;
	all_ate = 1;
	while (i < table->nphilos)
	{
		pthread_mutex_lock(&table->waiter);
		if (table->philos[i++].meals_eaten < table->nmeals)
			all_ate = 0;
		pthread_mutex_unlock(&table->waiter);
		if (!all_ate)
			break ;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&table->waiter);
		table->death_flag = 1;
		pthread_mutex_unlock(&table->waiter);
	}
	return (all_ate);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_death(table))
			break ;
		if (check_all_ate(table))
			break ;
		ft_usleep(10);
	}
	return (NULL);
}
