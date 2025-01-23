/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:48:07 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/01/23 17:38:19 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthreads.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	/* data */
}			t_philosopher;

typedef struct s_table
{
	t_philosopher	*philos;
	long			nphilosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nmeals;
	
}			t_table;

void	check_args(int ac, char **av);
void	print_valid_args(void);

#endif
