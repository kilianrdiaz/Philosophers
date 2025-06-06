/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:57:01 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/06/06 19:58:54 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void    stop(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nmeals)
    {
        pthread_join(table->philos[i].thread, NULL);
        i++;
    }
    
}

// Creacion de hilos (filosofos)
static int    start(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nphilos)
    {
        /* if (pthread_create(&table->philos[++i].thread, NULL, routine, table->philos) != 0)
            return (1);
        printf("test\n"); */
        pthread_create(&table->philos[i].thread, NULL, routine, table->philos);
    }
    return (0);
}

// Main
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
    }
    else
        print_valid_args();
    stop(table);
    return (EXIT_FAILURE);
}
