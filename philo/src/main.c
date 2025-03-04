/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:57:01 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/03/04 14:01:10 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// Creacion de hilos (filosofos)
void    start(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nphilos)
    {
        pthread_create(&table->philos[i++].thread, NULL, routine, table);
    }
}

// Main
int main(int ac, char **av)
{
    t_table table;
    
    if (ac == 5 || ac == 6)
    {
        check_args();
        init_table(&table, av, ac);
        start(&table);
    }
    else
        print_valid_args();
}
