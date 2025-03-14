/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:38:42 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/14 13:52:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_philo(t_table table, int id)
{
	table->philos[i - 1].id = id;
}

void	init_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nphilosophers)
		init_philo(table, ++i);
}
