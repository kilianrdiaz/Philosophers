/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:57:01 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/01/23 17:36:13 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int main(int ac, char **av)
{
    t_table table;
    
    if (ac == 5 || ac == 6)
    {
        check_args();
        table.nphilosophers = ft_atol(av[1]);
		table.time_to_die = ft_atol(av[2]);
		table.time_to_eat = ft_atol(av[3]);
		table.time_to_sleep = ft_atol(av[4]);
		if (ac == 6)
        	table.nmeals = ft_atol(av[5]);
    }
    else
        print_valid_args();
}
