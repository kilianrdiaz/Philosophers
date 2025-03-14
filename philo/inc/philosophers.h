/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:48:07 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/14 13:52:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthreads.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	int			id;
	int			eating;
	int				meals_eaten;
	pthread_mutex_t	
}			t_philosopher;

typedef struct s_table
{
	t_philosopher	philos[250];
	pthread_mutex_t	forks[250];
	long			nphilosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nmeals;
}			t_table;

void	check_args(int ac, char **av);
void	print_valid_args(void);

#endif
