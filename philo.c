#include "philo.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

// Convert to Milliseconds: The seconds (tv.tv_sec) are multiplied by 1000
// to convert to milliseconds. The microseconds (tv.tv_usec) are divided by 1000
//  to convert to milliseconds. These two values are added together to get
//  the current timestamp in milliseconds.

void *timestamp_ms()
{
    struct timeval tv;
    long ms;

    gettimeofday(&tv, NULL);
    printf("tv_sec = %li\n", tv.tv_sec);
    printf("tv_usec = %li\n", tv.tv_usec);
    ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    printf("%li\n", ms);
    return NULL;    
}

void thread_philo(int  *args)
{
    pthread_t tpid;
    int nbr_of_philo;

    nbr_of_philo = args[0];
    printf("nbr of philo = %i\n", nbr_of_philo);
    pthread_create(&tpid, NULL, timestamp_ms, NULL);
    pthread_join(tpid, NULL);
}

void err_message(int err)
{
    if (err == 1)
        printf("Error: Arguments\n");
    if (err == 2)
        printf("Error: Invalid Arguments\n");
}

int main(int ac, char **av)
{
    int args[ac - 1];

    if (ac < 5 || ac > 6)
    {
        err_message(1);
        return (1);
    }
    if (!args_handling(ac, av, args))
        err_message(2);
    thread_philo(args);
    //print arguments value
    for(int x = 0; x < ac - 1; x++)
        printf("val = %i\n", args[x]);
    return (0);
}