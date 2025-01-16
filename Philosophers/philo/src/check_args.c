#include "../inc/philosophers.h"

static void	print_valid_args(void)
{
	printf("== Wrong Arguments ==\n");
	printf("Expected values:\n");
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

	i = 1;
	if (ac != 5 && ac != 6)
		print_valid_args();
	while (i < ac)
	{
		
	}
}
