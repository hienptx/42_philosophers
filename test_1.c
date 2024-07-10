#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define QUIT_COLOR "\033[0m"

typedef struct s_philo_attr
{
	pthread_t		monitor_thread;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				stop_status;
	long			start;
	struct s_philo	*attr;
}					t_philo_attr;

typedef struct s_philo
{
	int				philo_id;
	int				done_eating;
	int				meals_eaten;
	int				*is_dead;
	long			last_meal;
	pthread_t		p_thread;
	t_philo_attr	*shared_attr;
}					t_philo;

long	get_time_now(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	err_message(int code)
{
	if (code == 1)
	{
		printf("Invalid number of arguments.\n");
	}
	else if (code == 2)
	{
		printf("Error in argument handling.\n");
	}
}

void	destroy_and_free(t_philo_attr *p_attr)
{
	int	i;

	for (i = 0; i < p_attr->nbr_of_philo; ++i)
		pthread_mutex_destroy(&p_attr->fork_mutexes[i]);
	pthread_mutex_destroy(&p_attr->death_mutex);
	pthread_mutex_destroy(&p_attr->write_mutex);
	pthread_mutex_destroy(&p_attr->meal_mutex);
	free(p_attr->fork_mutexes);
	free(p_attr->attr);
}

void	return_message(char *str, t_philo_attr *attr, int id)
{
	pthread_mutex_lock(&attr->write_mutex);
	printf("%li %i %s", get_time_now() - attr->start, id, str);
	pthread_mutex_unlock(&attr->write_mutex);
}

int	check_simulation_status(t_philo_attr *ptr)
{
	int	status;

	pthread_mutex_lock(&ptr->death_mutex);
	status = ptr->stop_status;
	pthread_mutex_unlock(&ptr->death_mutex);
	return (status);
}

void	eat(t_philo *attr, int left, int right, int id)
{
	// printf("id = %i, left = %i, right = %i \n", id, left, right);
	pthread_mutex_lock(&attr->shared_attr->fork_mutexes[right]);
	pthread_mutex_lock(&attr->shared_attr->fork_mutexes[left]);
	return_message(GREEN " has taken right fork\n" QUIT_COLOR, attr->shared_attr,
		id);
	return_message(GREEN " has taken left fork\n" QUIT_COLOR, attr->shared_attr,
		id);
	attr->done_eating = 1;
	return_message(CYAN " is eating\n" QUIT_COLOR, attr->shared_attr, id);
	pthread_mutex_lock(&attr->shared_attr->meal_mutex);
	attr->meals_eaten++;
	attr->last_meal = get_time_now();
	pthread_mutex_unlock(&attr->shared_attr->meal_mutex);
	attr->done_eating = 0;
	usleep(attr->shared_attr->time_to_eat * 1000);
	pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[right]);
	pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[left]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int	left;
	int	right;
    // int temp;

	philo = (t_philo *)arg;
    right = philo->philo_id - 1;
    left = philo->philo_id % philo->shared_attr->nbr_of_philo;
	if (philo->philo_id % 2 == 0)
	{
		left = philo->philo_id - 1;
		right = philo->philo_id % philo->shared_attr->nbr_of_philo;
	}
	while (check_simulation_status(philo->shared_attr))
	{
		eat(philo, left, right, philo->philo_id);

		return_message(RED " is sleeping\n" QUIT_COLOR, philo->shared_attr,
			philo->philo_id);
		usleep(philo->shared_attr->time_to_sleep * 1000);

		return_message(PURPLE " is thinking\n" QUIT_COLOR, philo->shared_attr,
			philo->philo_id);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo_attr	*attr;
	int				all_ate;

	attr = (t_philo_attr *)arg;
	while (check_simulation_status(attr))
	{
		all_ate = 0;
		for (int i = 0; i < attr->nbr_of_philo; ++i)
		{
			pthread_mutex_lock(&attr->death_mutex);
			if (get_time_now() - attr->attr[i].last_meal >= attr->time_to_die
				&& !attr->attr[i].done_eating)
			{
				// printf("die time %li\n", get_time_now() - attr->attr[i].last_meal);
				return_message(" died\n", attr, attr->attr[i].philo_id);
				attr->stop_status = 0;
				pthread_mutex_unlock(&attr->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&attr->death_mutex);

			if (attr->nbr_of_meals != -1
				&& attr->attr[i].meals_eaten >= attr->nbr_of_meals)
			{
				pthread_mutex_lock(&attr->meal_mutex);
				all_ate++;
				pthread_mutex_unlock(&attr->meal_mutex);
			}
		}
		if (all_ate == attr->nbr_of_philo)
		{
			pthread_mutex_lock(&attr->death_mutex);
			attr->stop_status = 0;
			pthread_mutex_unlock(&attr->death_mutex);
			break ;
		}
	}
	return (NULL);
}

int	create_threads(t_philo_attr *p_attr)
{
	int	i;

	if (pthread_create(&p_attr->monitor_thread, NULL, &monitor, p_attr) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (-1);
	}
	for (i = 0; i < p_attr->nbr_of_philo; ++i)
	{
		if (pthread_create(&p_attr->attr[i].p_thread, NULL, philo_routine,
				&p_attr->attr[i]) != 0)
		{
			printf("Failed to create philosopher thread %d\n", i + 1);
			return (-1);
		}
	}
	if (pthread_join(p_attr->monitor_thread, NULL) != 0)
	{
		printf("Failed to join monitor thread\n");
		return (-1);
	}
	for (i = 0; i < p_attr->nbr_of_philo; ++i)
	{
		if (pthread_join(p_attr->attr[i].p_thread, NULL) != 0)
		{
			printf("Failed to join philosopher thread %d\n", i + 1);
			return (-1);
		}
	}
	return (0);
}

int	fork_mutexes(t_philo_attr *p_attr)
{
	int	i;

	p_attr->fork_mutexes = malloc(p_attr->nbr_of_philo
			* sizeof(pthread_mutex_t));
	if (p_attr->fork_mutexes == NULL)
	{
		printf("Failed to allocate memory for fork mutexes\n");
		return (-1);
	}
	for (i = 0; i < p_attr->nbr_of_philo; ++i)
		pthread_mutex_init(&p_attr->fork_mutexes[i], NULL);
	if (create_threads(p_attr) != 0)
	{
		free(p_attr->fork_mutexes);
		return (-1);
	}
	return (0);
}

void	init_philo(t_philo_attr *ptr)
{
	int	i;

	ptr->attr = malloc(ptr->nbr_of_philo * sizeof(t_philo));
	if (ptr->attr == NULL)
	{
		printf("Failed to allocate memory for philosophers\n");
		return ;
	}
	for (i = 0; i < ptr->nbr_of_philo; ++i)
	{
		ptr->attr[i].philo_id = i + 1;
		ptr->attr[i].done_eating = 0;
		ptr->attr[i].meals_eaten = 0;
		ptr->attr[i].is_dead = &ptr->stop_status;
		ptr->attr[i].last_meal = get_time_now();
		ptr->attr[i].shared_attr = ptr;
	}
}

void	init_shared_data(int ac, int *args, t_philo_attr *ptr)
{
	ptr->stop_status = 1;
	ptr->nbr_of_philo = args[0];
	ptr->time_to_die = args[1];
	ptr->time_to_eat = args[2];
	ptr->time_to_sleep = args[3];
	ptr->start = get_time_now();
	ptr->nbr_of_meals = (ac == 6) ? args[4] : -1;
	pthread_mutex_init(&ptr->death_mutex, NULL);
	pthread_mutex_init(&ptr->write_mutex, NULL);
	pthread_mutex_init(&ptr->meal_mutex, NULL);
}

int	main(int ac, char **av)
{
	t_philo_attr p_attr;
	int args[ac - 1];

	if (ac < 5 || ac > 6)
	{
		err_message(1);
		return (1);
	}
	if (!args_handling(ac, av, args))
	{
		err_message(2);
		return (1);
	}
	init_shared_data(ac, args, &p_attr);
	init_philo(&p_attr);
	if (fork_mutexes(&p_attr) != 0)
	{
		destroy_and_free(&p_attr);
		return 1;
	}
	destroy_and_free(&p_attr);
	return 0;
}