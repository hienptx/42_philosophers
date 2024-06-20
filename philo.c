#include "philo.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
void err_message(int err)
{
    if (err == 1)
        printf("Error: Number of Arguments is 4 or 5");
}

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        err_message(1);
        return (0);
    }
    args_handling(ac, av);
    return (0);
}