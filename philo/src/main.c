#include "../inc/philosophers.h"

int main(int ac, char **av)
{
    t_table table;
    
    if (ac == 5 || ac == 6)
    {
        check_args();
        table.nphilosophers = ft_atol(av[1]);
        table.nmeals = ft_atol();
    }
    else
        print_valid_args();
}