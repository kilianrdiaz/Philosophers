#include "philosophers_bonus.c"

void	routine(t_philo *philo)
{
	while (1)
	{
		print_status(philo, "is thinking");
		sem_wait(philo->data->forks);
		print_status(philo, "has taken a fork");
		sem_wait(philo->data->forks);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
		ft_usleep(philo->data->time_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		if (philo->data->must_eat_count != -1
			&& philo->meals_eaten >= philo->data->must_eat_count)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long long time;

	sem_wait(philo->data->print);
	time = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, philo->id, status);
	sem_post(philo->data->print);
}