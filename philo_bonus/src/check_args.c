/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:50:21 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/06 17:34:17 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

// Muestra los argumentos esperados por el programa
void	print_valid_args(void)
{
	printf("== Wrong Arguments ==\n");
	printf("Expected values:\n./philo\n");
	printf("->\tnumber_of_philosophers\n");
	printf("->\ttime_to_die\n");
	printf("->\ttime_to_eat\n");
	printf("->\ttime_to_sleep\n");
	printf("->\tnumber_of_times_each_philosopher_must_eat (*optional*)\n");
	exit(EXIT_SUCCESS);
}

// Checkea si los argumentos pasados son correctos
void	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				print_valid_args();
			j++;
		}
		i++;
	}
	return ;
}
