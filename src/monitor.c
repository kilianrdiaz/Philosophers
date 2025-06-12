#include "philosophers.h"

// Función para verificar si debe continuar la simulación
int	should_continue(t_philo *philo)
{
	int	continue_sim;

	pthread_mutex_lock(&philo->table->waiter);
	if (philo->table->death_flag)
		continue_sim = 0;
	else if (philo->table->nmeals != -1 && philo->meals_eaten >= philo->table->nmeals)
		continue_sim = 0;
	else
		continue_sim = 1;
	pthread_mutex_unlock(&philo->table->waiter);
	
	return (continue_sim);
}

static int check_death(t_table *table)
{
    int i;
    long current_time;
    
    i = 0;
    while (i < table->nphilos)
    {
        pthread_mutex_lock(&table->waiter);
        current_time = get_time_ms();
        
        if ((current_time - table->philos[i].time_last_meal) > table->time_to_die)
        {
            pthread_mutex_unlock(&table->waiter);
            print_status(&table->philos[i], "died");
            /*i = 0;
            while (i < table->nphilos)
            {
                printf("Meals: %d\n", table->philos[i].meals_eaten);
                i++;
            }*/
            pthread_mutex_lock(&table->waiter);
            table->death_flag = 1;
            pthread_mutex_unlock(&table->waiter);
            return (1);
        }
        pthread_mutex_unlock(&table->waiter);
        i++;
    }
    return (0);
}

// Función para verificar si todos han comido suficiente
static int check_all_ate(t_table *table)
{
    int i;
    int all_ate;
    
    if (table->nmeals == -1)
        return (0);
    i = 0;
    all_ate = 1;
    while (i < table->nphilos)
    {
        pthread_mutex_lock(&table->waiter);
        if (table->philos[i].meals_eaten < table->nmeals)
            all_ate = 0;
        pthread_mutex_unlock(&table->waiter);
        if (!all_ate)
            break;
        i++;
    }
    if (all_ate)
    {
        pthread_mutex_lock(&table->waiter);
        table->death_flag = 1;
        pthread_mutex_unlock(&table->waiter);
        return (1);
    }
    return (0);
}

// Monitor principal
void *monitor(void *arg)
{
    t_table *table;

    table = (t_table *)arg;

    while (1)
    {
        if (check_death(table) || check_all_ate(table))
            break;
        ft_usleep(10);
    }
    return (NULL);
}