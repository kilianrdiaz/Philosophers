/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:32 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/04 14:01:08 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_action(t_philo philo, int id, char *action)
{
	long	actual_time;

	pthread_mutex_lock(&philo->table->writing);
	if (!philo->table->dead)
	{
		actual_time = get_time_ms() - philo->table->start_time;
		printf("%ld ", &actual_time);
		printf("%d", &philo->id);
		printf("%s \n", action);
	}
	pthread_mutex_unlock(&philo->table->writing);
}

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
