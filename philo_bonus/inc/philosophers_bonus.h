/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:48:07 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/11 21:30:39 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_philo
{
	/* data */
	int				id;
	long			time_last_meal;
	int				meals_eaten;
	pid_t			pid;
	struct s_table	*table;
}			t_philo;

typedef struct s_table
{
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print;
    int				death_flag;
	long			nphilos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nmeals;
	long			start_time;
}			t_table;

void	check_args(int ac, char **av);
t_table	*init_table(char **av, int ac);
void	print_valid_args(void);
void	print_status(t_philo *philo, char *action);
void	cleanup_table(t_table *table);
void	*routine(void *arg);
void	*monitor(void *arg);
int		ft_isdigit(char c);
int		should_continue(t_philo *philo);
int		ft_usleep(size_t milliseconds);
long	get_time_ms(void);
long	ft_atol(const char *s);

#endif