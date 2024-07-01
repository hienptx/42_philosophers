/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/07/01 20:16:41 by hipham           ###   ########.fr       */
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
	pthread_t		monitor_thread;

	i = -1;
	if (pthread_create(&monitor_thread, NULL, &monitor, (void *)attr) != 0)
		ft_free(monitor_thread);
	while (++i < attr->nbr_of_philo)
	{
		p_attr[i].philo_id = i + 1;
		p_attr[i].attr = attr;
		if (pthread_create(&attr->p_thread[i], NULL, philo_routine, (void *)&p_attr[i]) != 0)
			ft_free(attr->p_thread);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		ft_free(monitor_thread);
	i = -1;
	while (++i < attr->nbr_of_philo)
	{ 
		if (pthread_join(attr->p_thread[i], NULL) != 0)
			ft_free(attr->p_thread);
	}
	return (1);
}

void destroy_and_free(t_philo_attr *p_attr)
{
	int i;

	i = -1;
	pthread_mutex_destroy(&p_attr->death_mutex);
	pthread_mutex_destroy(&p_attr->write_mutex);
	pthread_mutex_destroy(&p_attr->meal_mutex);
	while (++i < p_attr->attr->nbr_of_philo)
		pthread_mutex_destroy(&p_attr->attr->fork_mutexes[i]);
	free(p_attr->attr->fork_mutexes);
	free(p_attr->attr->p_thread);
	free(p_attr);
}

void	*fork_mutexes(t_philo *attr, t_philo_attr *p_attr)
{
	int 		i;
	
	i = -1;
	attr->fork_mutexes = malloc(attr->nbr_of_philo * sizeof(pthread_mutex_t)); // FREE
	if (attr->fork_mutexes == NULL)
		malloc_error(attr->fork_mutexes);
	while (++i < attr->nbr_of_philo)
		pthread_mutex_init(&attr->fork_mutexes[i], NULL);
	if(!create_threads(p_attr, attr))
		return (NULL);
	i = -1;	
	while (++i < attr->nbr_of_philo)
		pthread_mutex_destroy(&attr->fork_mutexes[i]);
	return (NULL);
}

void init_program(t_philo *attr, t_philo_attr *p_attr)
{
	attr->p_thread = malloc(attr->nbr_of_philo * sizeof(pthread_t)); //FREE
	malloc_error(attr->p_thread);
	p_attr = malloc(attr->nbr_of_philo * sizeof(t_philo_attr)); //FREE
	malloc_error(attr->p_thread);
	pthread_mutex_init(&p_attr->death_mutex, NULL);
	pthread_mutex_init(&p_attr->write_mutex, NULL);
	pthread_mutex_init(&p_attr->meal_mutex, NULL);
}

void init_philos(int ac, int *args, t_philo *ph, t_philo_attr *ph_attr)
{
	int i;

	ph->nbr_of_philo = args[0];
	ph->time_to_die = args[1];
	ph->time_to_eat = args[2];
	ph->time_to_sleep = args[3];
	if (ac == 6)
		ph->nbr_of_meals = args[4];
	else
		ph->nbr_of_meals = -1;
	i = -1;
	while (++i < ph->nbr_of_philo)
	{
		ph[i].done_eating = 0;
		ph[i].meals_eaten = 0;
		ph[i].is_dead = 0;
		ph[i].last_meal = get_time_now();
		ph[i].start = get_time_now();
		ph[i].death_mutex = &ph_attr->death_mutex;
		ph[i].write_mutex = &ph_attr->write_mutex;
		ph[i].meal_mutex = &ph_attr->meal_mutex;
	}
}

int	main(int ac, char **av)
{
	t_philo			attr;
	t_philo_attr	p_attr;
	int				args[ac - 1];

	if (ac < 5 || ac > 6)
	{
		err_message(1);
		return (1);
	}
	if (!args_handling(ac, av, args))
		err_message(2);
	init_philos(ac, args, &attr, &p_attr);
	init_program(&attr, &p_attr);
	fork_mutexes(&attr, &p_attr);
	destroy_and_free(&p_attr);
	return (0);
}

// print arguments value
// for(int x = 0; x < ac - 1; x++)
//     printf("val = %i\n", args[x]);
