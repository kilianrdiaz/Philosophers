/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:57:01 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/11 21:15:22 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int start(t_table *table)
{
    int     i;

    table->start_time = get_time_ms();
    i = 0;
    while (i < table->nphilos)
    {
        table->philos[i].time_last_meal = table->start_time;
        i++;
    }
    return (0)
}

int main(int ac, char **av)
{
    t_table *table;
    
    table = NULL;
    if (ac == 5 || ac == 6)
    {
        check_args(ac, av);
        table = init_table(av, ac);
        if (!table)
            return (EXIT_FAILURE);
        if (start(table) == 1)
            return (EXIT_FAILURE);
        cleanup_table(table);
        return (EXIT_SUCCESS);
    }
    else
        print_valid_args();
    return (EXIT_FAILURE);
}
