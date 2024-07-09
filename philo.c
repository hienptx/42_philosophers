/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 20:20:57 by hipham           ###   ########.fr       */
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

int create_threads(t_philo *ph, int nbr_of_philos)
{
	int i;

	i= -1;
	while (++i < nbr_of_philos)
	{
		if (pthread_create(&ph[i].p_thread, NULL, philo_routine, (void *)&ph[i]) != 0)
		{
			printf("Failed to create philos' threads\n");
			ft_free(ph->p_thread);
		}
	}
	if (pthread_create(&ph->monitor, NULL, &monitor, (void *)ph) != 0)
	{
		printf("Failed to create monitor's thread\n");
		ft_free(ph->monitor);
	}
	i = -1;
	while (++i < nbr_of_philos)
	{ 
		if (pthread_join(ph[i].p_thread, NULL) != 0)
		{
			printf("Failed to join philos' threads\n");
			ft_free(ph->monitor);
			ft_free(ph->p_thread);
		}
	}
	if (pthread_join(ph->monitor, NULL) != 0)
	{
		printf("Failed to create monitor's thread\n");
		ft_free(ph->monitor);
		ft_free(ph->p_thread);
	}
	return (1);
}

void	*fork_mutexes(t_philo *attr)
{
	int 		i;

	attr->fork_mutexes = malloc(attr->itable.nbr_of_philo * sizeof(pthread_mutex_t)); // FREE
	if (attr->fork_mutexes == NULL)
	{
		printf("Failed to allocate maloc\n");
		return(NULL);
	}
	i = -1;
	while (++i < attr->itable.nbr_of_philo)
	{
		if (pthread_mutex_init(&attr->fork_mutexes[i], NULL) != 0)
		{
			printf("Failed to init fork's mutexes\n");
			free(attr->fork_mutexes);
		}
	}
	return (NULL);
}

// void allocate_threads(pthread_t monitor, pthread_t *philo, int nbr_of_philo)
// {
// 	monitor = malloc(sizeof(pthread_t)); // FREE THIS
// 	if (monitor == NULL)
// 	{
// 		printf("Malloc failed to allocate memory for monitor\n");
// 		return (NULL);
// 	}
// 	philo = malloc(nbr_of_philo * sizeof(pthread_t)); //FREE
// 	if (philo == NULL)
// 	{
// 		printf("Malloc failed to allocate memory for philo\n");
// 		free(monitor);
// 		return (NULL);
// 	}
// }

int	main(int ac, char **av)
{
	t_philo			attr[NUM_PHILOSOPHERS];
	// t_philo_mtx		p_attr[NUM_PHILOSOPHERS];
	int				args[ac - 1];

	if (ac < 5 || ac > 6)
	{
		err_message(1);
		return (1);
	}
	if (!args_handling(ac, av, args))
		err_message(2);
	get_philo_info(attr, args, ac);
	init_philos(attr);
	init_mutexes(attr->mtx);
	// allocate_threads(attr->monitor, attr->p_thread, attr->itable->nbr_of_philo);
	fork_mutexes(attr);
	if(!create_threads(attr, attr->itable.nbr_of_philo))
		return (0);
	destroy_and_free(attr);
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
