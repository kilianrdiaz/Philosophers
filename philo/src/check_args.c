#include "../inc/philosophers.h"

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
			if (!ft_isdigit(av[i][j]))	//TODO
				print_valid_args();
			j++;
		}
		i++;
	}
	return ;
}