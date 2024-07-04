// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/time.h>
// #include <unistd.h>

// #define NUM_PHILOSOPHERS 250

// # define BLACK "\033[0;30m"
// # define RED "\033[0;31m"
// # define GREEN "\033[0;32m"
// # define YELLOW "\033[0;33m"
// # define BLUE "\033[0;34m"
// # define PURPLE "\033[0;35m"
// # define CYAN "\033[0;36m"
// # define WHITE "\033[0;37m"
// # define QUIT_COLOR "\033[0m"

// typedef struct s_philo
// {
// 	int				nbr_of_philo;
// 	long			time_to_die;
// 	long			time_to_sleep;
// 	long			time_to_eat;
// 	int				nbr_of_meals;
// 	int				done_eating;
// 	int				meals_eaten;
// 	int				is_dead;
// 	long			start;
// 	long			last_meal;
// 	pthread_t		*p_thread;
// 	pthread_mutex_t	meal_mutex;
// 	pthread_mutex_t	death_mutex;
// 	pthread_mutex_t	write_mutex;
// 	pthread_mutex_t	waiter;
// 	pthread_mutex_t	*fork_mutexes;
// }					t_philo;

// typedef struct s_philo_attr
// {
// 	int				philo_id;
// 	t_philo			*attr;
// }					t_philo_attr;

// long	get_time_now(void)
// {
// 	struct timeval	tv;
// 	long			ms;

// 	gettimeofday(&tv, NULL);
// 	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
// 	return (ms);
// }

// long	timestamp_ms(t_philo *attr)
// {
// 	long	now;
// 	long	ret;

// 	now = get_time_now();
// 	;
// 	ret = now - attr->start;
// 	return (ret);
// }

// int	if_dead(t_philo_attr *p_attr)
// {
// 	int	is_dead;

// 	is_dead = 1;
// 	is_dead = p_attr->attr->is_dead;
// 	return (is_dead);
// }

// void	return_message(char *str, t_philo *attr, int id)
// {
// 	pthread_mutex_lock(&attr->write_mutex);
// 	printf("%li %i %s", timestamp_ms(attr), id, str);
// 	pthread_mutex_unlock(&attr->write_mutex);
// }

// void	eat(t_philo *attr, int id)
// {
// 	int	left;
// 	int	right;

// 	left = id - 1;
// 	right = (id + 1) % attr->nbr_of_philo;

// 	// Request both forks from the waiter
// 	pthread_mutex_lock(&attr->waiter);
// 	pthread_mutex_lock(&attr->fork_mutexes[left]);
// 	return_message(" has taken l-fork\n", attr, id);
    
// 	pthread_mutex_lock(&attr->fork_mutexes[right]);
// 	return_message("has taken r-fork\n", attr, id);
// 	pthread_mutex_unlock(&attr->waiter);
	
//     return_message("is eating\n", attr, id);
// 	usleep(attr->time_to_eat * 1000);

// 	pthread_mutex_lock(&attr->meal_mutex);
// 	attr->last_meal = get_time_now();
// 	attr->done_eating = 1;
// 	attr->meals_eaten++;
// 	pthread_mutex_unlock(&attr->meal_mutex);
	
//     pthread_mutex_unlock(&attr->fork_mutexes[right]);
// 	pthread_mutex_unlock(&attr->fork_mutexes[left]);
// }

// void	*philo_routine(void *arg)
// {
// 	t_philo_attr	*p_attr;

// 	p_attr = (t_philo_attr *)arg;
// 	while (1)
// 	{
// 		return_message("is thinking\n", p_attr->attr, p_attr->philo_id);
// 		eat(p_attr->attr, p_attr->philo_id);
// 		return_message("is sleeping\n", p_attr->attr, p_attr->philo_id);
// 		usleep(p_attr->attr->time_to_sleep * 1000);
// 	}
// 	return (arg);
// }

// int	create_threads(t_philo *attr, t_philo_attr *p_attr)
// {
// 	for (int i = 0; i < attr->nbr_of_philo; i++)
// 	{
// 		p_attr[i].philo_id = i + 1;
// 		p_attr[i].attr = attr;
// 		if (pthread_create(&attr->p_thread[i], NULL, philo_routine,
// 				(void *)&p_attr[i]) != 0)
// 		{
// 			perror("Failed to create thread");
// 			return (0);
// 		}
// 	}
// 	for (int i = 0; i < attr->nbr_of_philo; i++)
// 	{
// 		if (pthread_join(attr->p_thread[i], NULL) != 0)
// 		{
// 			perror("Failed to join thread");
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// void	destroy_and_free(t_philo *attr)
// {
// 	for (int i = 0; i < attr->nbr_of_philo; i++)
// 	{
// 		pthread_mutex_destroy(&attr->fork_mutexes[i]);
// 	}
// 	pthread_mutex_destroy(&attr->meal_mutex);
// 	pthread_mutex_destroy(&attr->death_mutex);
// 	pthread_mutex_destroy(&attr->write_mutex);
// 	pthread_mutex_destroy(&attr->waiter);
// 	free(attr->fork_mutexes);
// 	free(attr->p_thread);
// }

// void	*fork_mutexes(t_philo *attr, t_philo_attr *p_attr)
// {
// 	attr->p_thread = malloc(attr->nbr_of_philo * sizeof(pthread_t));
// 	if (attr->p_thread == NULL)
// 		return (NULL);
// 	attr->fork_mutexes = malloc(attr->nbr_of_philo * sizeof(pthread_mutex_t));
// 	if (attr->fork_mutexes == NULL)
// 	{
// 		free(attr->p_thread);
// 		return (NULL);
// 	}
// 	for (int i = 0; i < attr->nbr_of_philo; i++)
// 	{
// 		pthread_mutex_init(&attr->fork_mutexes[i], NULL);
// 	}
// 	if (!create_threads(attr, p_attr))
// 	{
// 		return (NULL);
// 	}
// 	destroy_and_free(attr);
// 	return (NULL);
// }

// // void init_program(t_philo *attr)
// // {
// //     pthread_mutex_init(&attr->death_mutex, NULL);
// //     pthread_mutex_init(&attr->write_mutex, NULL);
// //     pthread_mutex_init(&attr->meal_mutex, NULL);
// //     pthread_mutex_init(&attr->waiter, NULL);
// // }

// void	init_philos(int ac, int *args, t_philo *ph, t_philo_attr *ph_attr)
// {
// 	ph->nbr_of_philo = args[0];
// 	ph->time_to_die = args[1];
// 	ph->time_to_eat = args[2];
// 	ph->time_to_sleep = args[3];
// 	ph->start = get_time_now();
// 	if (ac == 6)
// 		ph->nbr_of_meals = args[4];
// 	else
// 		ph->nbr_of_meals = -1;
// 	// for (int i = 1; i <= ph->nbr_of_philo; i++)
// 	// {
// 	//     ph_attr[i].philo_id = i;
// 	//     ph_attr[i].attr = ph;
// 	// }
// 	pthread_mutex_init(&ph->meal_mutex, NULL);
// 	pthread_mutex_init(&ph->death_mutex, NULL);
// 	pthread_mutex_init(&ph->write_mutex, NULL);
// 	pthread_mutex_init(&ph->waiter, NULL);
// }

// int	main(int ac, char **av)
// {
// 	t_philo			attr;
// 	t_philo_attr	p_attr[NUM_PHILOSOPHERS];
// 	int				args[ac - 1];

// 	if (ac < 5 || ac > 6)
// 	{
// 		fprintf(stderr, "Invalid number of arguments\n");
// 		return (1);
// 	}
// 	for (int i = 0; i < ac - 1; i++)
// 	{
// 		args[i] = atoi(av[i + 1]);
// 	}
// 	// init_program(&attr);
// 	init_philos(ac, args, &attr, p_attr);
// 	fork_mutexes(&attr, p_attr);
// 	return (0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 250
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define PURPLE "\033[0;35m"
#define RED "\033[0;31m"
#define QUIT_COLOR "\033[0m"

typedef struct s_philo_attr {
    int philo_id;
    struct s_philo *attr;
    pthread_t monitor_thread;
} t_philo_attr;

typedef struct s_philo {
    int nbr_of_philo;
    int nbr_of_meals;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long start;
    long *last_meal;
    int *meals_eaten;
    int *done_eating;
    int *is_dead;
    pthread_t *p_thread;
    pthread_mutex_t *fork_mutexes;
    pthread_mutex_t death_mutex;
    pthread_mutex_t write_mutex;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t waiter;
} t_philo;

int	ft_atoi(const char *str)
{
	int			i;
	int			neopo;
	int	output;

	i = 0;
	neopo = 1;
	output = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neopo = -neopo;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = (str[i] - '0') + (output * 10);
		i++;
	}
	return (output * neopo);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int x)
{
	if (!(48 <= x && x <= 57))
		return (0);
	return (1);
}

int	str_arg_handling(char *s)
{
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && ft_isspace(*s))
			s++;
		if (*s != '\0' && (*s == '-' || *s == '+'))
		{
			s++;
			if (*s == '\0')
				return (0);
		}
		if (*s != '\0' && !ft_isdigit(*s))
			return (0);
		if (*s != '\0' && ft_isdigit(*s))
		{
			while (*s != '\0' && ft_isdigit(*s))
				s++;
		}
		if (*s != '\0' && !ft_isspace(*s))
			return (0);
	}
	return (1);
}

int args_handling(int ac, char **av, int *args)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!str_arg_handling(av[i]))
            return (0);
        args[i - 1] = ft_atoi(av[i]);
        i++;
    }
    return (1);
}

long get_time_now() {
    // Implement a function that returns the current timestamp in milliseconds.
    // Placeholder implementation.
    return (long)(time(NULL) * 1000);
}

void ft_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}

void return_message(char *str, t_philo *attr, int id) {
    pthread_mutex_lock(&attr->write_mutex);
    printf("%li %i %s", get_time_now() - attr->start, id, str);
    pthread_mutex_unlock(&attr->write_mutex);
}

void check_death(t_philo *attr) {
    long time_since_last_meal;
    int i;

    while (1) {
        for (i = 0; i < attr->nbr_of_philo; i++) {
            pthread_mutex_lock(&attr->death_mutex);
            time_since_last_meal = get_time_now() - attr->last_meal[i];
            if (time_since_last_meal > attr->time_to_die && attr->done_eating[i] == 0) {
                attr->is_dead[i] = 1;
                return_message("has died\n", attr, i + 1);
                pthread_mutex_unlock(&attr->death_mutex);
                return;
            }
            pthread_mutex_unlock(&attr->death_mutex);
        }
        usleep(1000);
    }
}


void destroy_and_free(t_philo_attr *p_attr) {
    int i;

    for (i = 0; i < p_attr->attr->nbr_of_philo; i++) {
        pthread_mutex_destroy(&p_attr->attr->fork_mutexes[i]);
    }
    pthread_mutex_destroy(&p_attr->attr->death_mutex);
    pthread_mutex_destroy(&p_attr->attr->write_mutex);
    pthread_mutex_destroy(&p_attr->attr->meal_mutex);
    pthread_mutex_destroy(&p_attr->attr->waiter);
    free(p_attr->attr->fork_mutexes);
    free(p_attr->attr->p_thread);
    free(p_attr->attr->last_meal);
    free(p_attr->attr->meals_eaten);
    free(p_attr->attr->done_eating);
    free(p_attr->attr->is_dead);
}


void eat(t_philo *attr, int id) {
    int left = id - 1;
    int right = id % attr->nbr_of_philo;

    pthread_mutex_lock(&attr->waiter);
    pthread_mutex_lock(&attr->fork_mutexes[left]);
    return_message(GREEN" has taken l-fork\n"QUIT_COLOR, attr, id);
    pthread_mutex_lock(&attr->fork_mutexes[right]);
    return_message(GREEN"has taken r-fork\n"QUIT_COLOR, attr, id);
    pthread_mutex_unlock(&attr->waiter);
    return_message(CYAN"is eating\n"QUIT_COLOR, attr, id);
    usleep(attr->time_to_eat * 1000);
    pthread_mutex_lock(&attr->meal_mutex);
    attr->last_meal[id - 1] = get_time_now();
    attr->done_eating[id - 1] = 1;
    attr->meals_eaten[id - 1]++;
    pthread_mutex_unlock(&attr->meal_mutex);
    pthread_mutex_unlock(&attr->fork_mutexes[right]);
    pthread_mutex_unlock(&attr->fork_mutexes[left]);
}

void *philo_routine(void *arg) {
    t_philo_attr *p_attr = (t_philo_attr *)arg;

    while (1) {
        if (p_attr->attr->nbr_of_meals != -1) {
            if (p_attr->attr->meals_eaten[p_attr->philo_id - 1] >= p_attr->attr->nbr_of_meals)
                break;
        }
        if (p_attr->attr->is_dead[p_attr->philo_id - 1])
            break;
        eat(p_attr->attr, p_attr->philo_id);
        return_message(RED"is sleeping\n"QUIT_COLOR, p_attr->attr, p_attr->philo_id);
        usleep(p_attr->attr->time_to_sleep * 1000);
        return_message(PURPLE"is thinking\n"QUIT_COLOR, p_attr->attr, p_attr->philo_id);
    }
    printf("philo[%i] has eaten %i meals\n", p_attr->philo_id, p_attr->attr->meals_eaten[p_attr->philo_id - 1]);
    return NULL;
}

void init_philos(int ac, int *args, t_philo *ph) {
    int i;

    ph->nbr_of_philo = args[0];
    ph->time_to_die = args[1];
    ph->time_to_eat = args[2];
    ph->time_to_sleep = args[3];
    ph->start = get_time_now();
    ph->nbr_of_meals = (ac == 6) ? args[4] : -1;
    ph->last_meal = malloc(ph->nbr_of_philo * sizeof(long));
    ph->meals_eaten = malloc(ph->nbr_of_philo * sizeof(int));
    ph->done_eating = malloc(ph->nbr_of_philo * sizeof(int));
    ph->is_dead = malloc(ph->nbr_of_philo * sizeof(int));

    for (i = 0; i < ph->nbr_of_philo; i++) {
        ph->last_meal[i] = get_time_now();
        ph->meals_eaten[i] = 0;
        ph->done_eating[i] = 0;
        ph->is_dead[i] = 0;
    }

    pthread_mutex_init(&ph->death_mutex, NULL);
    pthread_mutex_init(&ph->write_mutex, NULL);
    pthread_mutex_init(&ph->meal_mutex, NULL);
    pthread_mutex_init(&ph->waiter, NULL);
}

int create_threads(t_philo_attr *p_attr, t_philo *attr) {
    int i;

    attr->p_thread = malloc(attr->nbr_of_philo * sizeof(pthread_t));
    if (attr->p_thread == NULL) {
        printf("Malloc failed to allocate memory for philosopher threads\n");
        return 0;
    }

    if (pthread_create(&p_attr->monitor_thread, NULL, (void *(*)(void *))check_death, (void *)attr) != 0) {
        printf("Failed to create monitor thread\n");
        ft_free(attr->p_thread);
        return 0;
    }

    for (i = 0; i < attr->nbr_of_philo; i++) {
        p_attr[i].philo_id = i + 1;
        p_attr[i].attr = attr;
        if (pthread_create(&attr->p_thread[i], NULL, philo_routine, (void *)&p_attr[i]) != 0) {
            printf("Failed to create philosopher thread %d\n", i);
            for (int j = 0; j < i; j++) {
                pthread_join(attr->p_thread[j], NULL);
            }
            ft_free(attr->p_thread);
            return 0;
        }
    }

    if (pthread_join(p_attr->monitor_thread, NULL) != 0) {
        printf("Failed to join monitor thread\n");
        ft_free(attr->p_thread);
        return 0;
    }

    for (i = 0; i < attr->nbr_of_philo; i++) {
        if (pthread_join(attr->p_thread[i], NULL) != 0) {
            printf("Failed to join philosopher thread %d\n", i);
        }
    }

    ft_free(attr->p_thread);

    return 1;
}

int main(int ac, char **av) {
    t_philo			attr[NUM_PHILOSOPHERS];
    t_philo_attr p_attr[NUM_PHILOSOPHERS];
    int args[ac - 1];

    if (ac < 5 || ac > 6) {
        fprintf(stderr, "Error: Incorrect number of arguments\n");
        return 1;
    }
    if (!args_handling(ac, av, args)) {
        fprintf(stderr, "Error: Argument handling failed\n");
        return 1;
    }

    init_philos(ac, args, attr);
    if (!create_threads(p_attr, attr)) {
        return 1;
    }
    destroy_and_free(p_attr);
    return 0;
}
