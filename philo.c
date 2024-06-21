#include "philo.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
void err_message(int err)
{
    if (err == 1)
        printf("Error: Arguments\n");
    if (err == 2)
        printf("Error: Invalid Arguments\n");
}

int main(int ac, char **av)
{
    // t_philo *agrs;

    // agrs = NULL;
    if (ac < 5 || ac > 6)
    {
        err_message(1);
        return (1);
    }
    if (!args_handling(ac, av))
        err_message(2);
    return (0);
}