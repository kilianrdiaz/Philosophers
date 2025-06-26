/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:32 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/21 14:36:13 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *s)
{
	int		i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i])
		return (0);
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * neg);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(50);
	return (0);
}

void	print_status(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write_lock);
	pthread_mutex_lock(&philo->table->waiter);
	if (philo->table->death_flag && action[0] != 'd')
	{
		pthread_mutex_unlock(&philo->table->waiter);
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->waiter);
	timestamp = get_time_ms() - philo->table->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->table->write_lock);
}
