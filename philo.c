/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/07/04 19:26:31 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

// Convert to Milliseconds: The seconds (tv.tv_sec) are multiplied by 1000
// to convert to milliseconds. The microseconds (tv.tv_usec) are divided by 1000
//  to convert to milliseconds. These two values are added together to get
//  the current timestamp in milliseconds.

int create_threads(t_philo_attr *p_attr, t_philo *attr)
{
	int i;

	i= -1;
	// if (pthread_create(&p_attr->monitor_thread, NULL, &monitor, (void *)attr) != 0)
	// {
	// 	printf("Failed to create thread");
	// 	ft_free(p_attr->monitor_thread);
	// }
	while (++i < attr->nbr_of_philo)
	{
		p_attr[i].philo_id = i + 1;
		p_attr[i].attr = attr;
		if (pthread_create(&attr->p_thread[i], NULL, philo_routine, (void *)&p_attr[i]) != 0)
			ft_free(attr->p_thread);
	}
	i = -1;
	// if (pthread_join(p_attr->monitor_thread, NULL) != 0)
	// {
	// 	printf("Failed to create thread");
	// 	ft_free(p_attr->monitor_thread);
	// }
	while (++i < attr->nbr_of_philo)
	{ 
		if (pthread_join(attr->p_thread[i], NULL) != 0)
			ft_free(attr->p_thread);
	}
	return (1);
}

void	*fork_mutexes(t_philo *attr, t_philo_attr *p_attr)
{
	int 		i;

	// p_attr->monitor_thread = malloc(sizeof(pthread_t)); // FREE THIS
	// if (p_attr->monitor_thread == NULL)
	// {
	// 	printf("Malloc failed to allocate memory\n");
	// 	return (0);
	// }
	attr->p_thread = malloc(attr->nbr_of_philo * sizeof(pthread_t)); //FREE
	if (attr->p_thread == NULL)
	{
		printf("Malloc failed to allocate memory\n");
		// free(p_attr->monitor_thread);
		return (0);
	}
	attr->fork_mutexes = malloc(attr->nbr_of_philo * sizeof(pthread_mutex_t)); // FREE
	if (attr->fork_mutexes == NULL)
	{
		free(attr->p_thread);
		return(NULL);
	}
	i = -1;
	while (++i < attr->nbr_of_philo)
		pthread_mutex_init(&attr->fork_mutexes[i], NULL);
	if(!create_threads(p_attr, attr))
		return (NULL);
	return (NULL);
}

void init_philos(int ac, int *args, t_philo *ph)
{
	int i;

	ph->nbr_of_philo = args[0];
	ph->time_to_die = args[1];
	ph->time_to_eat = args[2];
	ph->time_to_sleep = args[3];
	ph->start = get_time_now();
	if (ac == 6)
		ph->nbr_of_meals = args[4];
	else
		ph->nbr_of_meals = -1;
	i = -1;
	while (++i < ph->nbr_of_philo)
	{
		ph[i].done_eating = 0;
		ph[i].meals_eaten = 0;
		ph[i].is_dead = 1;
		ph[i].last_meal = get_time_now();
	}
	pthread_mutex_init(&ph->death_mutex, NULL);
	pthread_mutex_init(&ph->write_mutex, NULL);
	pthread_mutex_init(&ph->meal_mutex, NULL);
	pthread_mutex_init(&ph->waiter, NULL);
}

int	main(int ac, char **av)
{
	t_philo			attr[NUM_PHILOSOPHERS];
	t_philo_attr	p_attr[NUM_PHILOSOPHERS];
	int				args[ac - 1];

	if (ac < 5 || ac > 6)
	{
		err_message(1);
		return (1);
	}
	if (!args_handling(ac, av, args))
		err_message(2);
	init_philos(ac, args, attr);
	fork_mutexes(attr, p_attr);
	destroy_and_free(p_attr);
	return (0);
}

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
// 	if (!args_handling(ac, av, args))
// 		err_message(2);
// 	// init_program(&attr);
// 	init_philos(ac, args, &attr);
// 	fork_mutexes(&attr, p_attr);
// 	return (0);
// }
