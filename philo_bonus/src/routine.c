#include "philosophers_bonus.c"

void    routine(t_philo *philo)
{
    while (1)
    {
        // Pensar
        print_status(philo, "is thinking");
        
        // Tomar tenedores
        sem_wait(philo->data->forks);  // Tomar primer tenedor
        print_status(philo, "has taken a fork");
        
        sem_wait(philo->data->forks);  // Tomar segundo tenedor
        print_status(philo, "has taken a fork");
        
        // Comer
        print_status(philo, "is eating");
        philo->last_meal_time = get_time();
        philo->meals_eaten++;
        ft_usleep(philo->data->time_to_eat);
        
        // Liberar tenedores
        sem_post(philo->data->forks);
        sem_post(philo->data->forks);
        
        // Verificar si ya comió suficiente
        if (philo->data->must_eat_count != -1 && 
            philo->meals_eaten >= philo->data->must_eat_count)
            break;
        
        // Dormir
        print_status(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
    }
}

void print_status(t_philo *philo, char *status)
{
    long long time;
    
    sem_wait(philo->data->print);
    time = get_time() - philo->data->start_time;
    printf("%lld %d %s\n", time, philo->id, status);
    sem_post(philo->data->print);
}