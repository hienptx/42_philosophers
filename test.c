#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5

typedef struct s_philo
{
    int nbr_of_philo;
    long time_to_die;
    long time_to_sleep;
    long time_to_eat;
    int nbr_of_meals;
    int done_eating;
    int meals_eaten;
    int is_dead;
    long start;
    long last_meal;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t write_mutex;
    pthread_t *p_thread;
    pthread_mutex_t waiter;
    pthread_mutex_t *fork_mutexes;
} t_philo;

typedef struct s_philo_attr
{
    int philo_id;
    t_philo *attr;
} t_philo_attr;

long	get_time_now()
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

long	timestamp_ms(t_philo *attr)
{
	long			now;
	long			ret;

	now = get_time_now();;
	ret = now - attr->start;
	return (ret);
}


int if_dead(t_philo_attr *p_attr)
{
    int is_dead;
    is_dead = 1;
    is_dead = p_attr->attr->is_dead;
    return is_dead;
}

void return_message(char *str, t_philo *attr, int id)
{
    pthread_mutex_lock(&attr->write_mutex);
    printf("%li %i %s", timestamp_ms(attr), id, str);
    pthread_mutex_unlock(&attr->write_mutex);
}

void eat(t_philo *attr, int id)
{
    int left = id;
    int right = (id + 1) % attr->nbr_of_philo;

    // Request both forks from the waiter
    pthread_mutex_lock(&attr->waiter);
    pthread_mutex_lock(&attr->fork_mutexes[left]);
    return_message(" has taken l-fork\n", attr, id);
    pthread_mutex_lock(&attr->fork_mutexes[right]);
    return_message("has taken r-fork\n", attr, id);
    pthread_mutex_unlock(&attr->waiter);

    return_message("is eating\n", attr, id);
    usleep(attr->time_to_eat * 1000);

    pthread_mutex_lock(&attr->meal_mutex);
    attr->last_meal = get_time_now();
    attr->done_eating = 1;
    attr->meals_eaten++;
    pthread_mutex_unlock(&attr->meal_mutex);

    pthread_mutex_unlock(&attr->fork_mutexes[right]);
    pthread_mutex_unlock(&attr->fork_mutexes[left]);
}

void *philo_routine(void *arg)
{
    t_philo_attr *p_attr = (t_philo_attr *)arg;
    while (1)
    {
        return_message("is thinking\n", p_attr->attr, p_attr->philo_id);
        eat(p_attr->attr, p_attr->philo_id);
        return_message("is sleeping\n", p_attr->attr, p_attr->philo_id);
        usleep(p_attr->attr->time_to_sleep * 1000);
    }
    return (arg);
}

int create_threads(t_philo *attr, t_philo_attr *p_attr)
{
    for (int i = 0; i < attr->nbr_of_philo; i++)
    {
        p_attr[i].philo_id = i + 1;
        p_attr[i].attr = attr;
        if (pthread_create(&attr->p_thread[i], NULL, philo_routine, (void *)&p_attr[i]) != 0)
        {
            perror("Failed to create thread");
            return 0;
        }
    }

    for (int i = 0; i < attr->nbr_of_philo; i++)
    {
        if (pthread_join(attr->p_thread[i], NULL) != 0)
        {
            perror("Failed to join thread");
            return 0;
        }
    }
    return 1;
}

void destroy_and_free(t_philo *attr)
{
    for (int i = 0; i < attr->nbr_of_philo; i++)
    {
        pthread_mutex_destroy(&attr->fork_mutexes[i]);
    }
    pthread_mutex_destroy(&attr->meal_mutex);
    pthread_mutex_destroy(&attr->death_mutex);
    pthread_mutex_destroy(&attr->write_mutex);
    pthread_mutex_destroy(&attr->waiter);
    free(attr->fork_mutexes);
    free(attr->p_thread);
}

void *fork_mutexes(t_philo *attr, t_philo_attr *p_attr)
{
    attr->p_thread = malloc(attr->nbr_of_philo * sizeof(pthread_t));
    if (attr->p_thread == NULL)
        return (NULL);
    attr->fork_mutexes = malloc(attr->nbr_of_philo * sizeof(pthread_mutex_t));
    if (attr->fork_mutexes == NULL)
    {
        free(attr->p_thread);
        return (NULL);
    }
    for (int i = 0; i < attr->nbr_of_philo; i++)
    {
        pthread_mutex_init(&attr->fork_mutexes[i], NULL);
    }
    if (!create_threads(attr, p_attr))
    {
        return (NULL);
    }
    destroy_and_free(attr);
    return (NULL);
}

// void init_program(t_philo *attr)
// {
//     pthread_mutex_init(&attr->death_mutex, NULL);
//     pthread_mutex_init(&attr->write_mutex, NULL);
//     pthread_mutex_init(&attr->meal_mutex, NULL);
//     pthread_mutex_init(&attr->waiter, NULL);
// }

void init_philos(int ac, int *args, t_philo *ph, t_philo_attr *ph_attr)
{
    ph->nbr_of_philo = args[0];
    ph->time_to_die = args[1];
    ph->time_to_eat = args[2];
    ph->time_to_sleep = args[3];
    ph->start = get_time_now();
    if (ac == 6)
        ph->nbr_of_meals = args[4];
    else
        ph->nbr_of_meals = -1;
    // for (int i = 1; i <= ph->nbr_of_philo; i++)
    // {
    //     ph_attr[i].philo_id = i;
    //     ph_attr[i].attr = ph;
    // }
    pthread_mutex_init(&ph->meal_mutex, NULL);
    pthread_mutex_init(&ph->death_mutex, NULL);
    pthread_mutex_init(&ph->write_mutex, NULL);
    pthread_mutex_init(&ph->waiter, NULL);
}

int main(int ac, char **av)
{
    t_philo attr;
    t_philo_attr p_attr[NUM_PHILOSOPHERS];
    int args[ac - 1];

    if (ac < 5 || ac > 6)
    {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    for (int i = 0; i < ac - 1; i++)
    {
        args[i] = atoi(av[i + 1]);
    }

    // init_program(&attr);
    init_philos(ac, args, &attr, p_attr);
    fork_mutexes(&attr, p_attr);
    return 0;
}
