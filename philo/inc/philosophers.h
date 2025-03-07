/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:48:07 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/04 14:01:16 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthreads.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	/* data */
	int				id;
	long			time_last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_table			*table;
}			t_philo;

typedef struct s_table
{
	t_philo			philos[250];
	pthread_mutex_t	forks[250];
	pthread_mutex_t	waiter;
	pthread_mutex_t	writing;
	long			nphilos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nmeals;
	long			start_time;
	int				dead;
	
}			t_table;

void	check_args(int ac, char **av);
void	print_valid_args(void);
void	routine(void *arg);
long	get_time_ms(void)

#endif