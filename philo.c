/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/07/10 20:02:42 by hipham           ###   ########.fr       */
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

int	check_simulation_status(t_philo_attr *ptr)
{
	int	status;

	pthread_mutex_lock(&ptr->death_mutex);
	status = ptr->stop_status;
	pthread_mutex_unlock(&ptr->death_mutex);
	return (status);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int	left;
	int	right;

	philo = (t_philo *)arg;
    right = philo->philo_id - 1;
    left = philo->philo_id % philo->shared_attr->nbr_of_philo;
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (check_simulation_status(philo->shared_attr))
	{
		eating(philo, left, right, philo->philo_id);
		sleeping(philo, philo->philo_id);
		thinking(philo, philo->philo_id);
	}
	return (NULL);
}

int	create_threads(t_philo_attr *p_attr)
{
	int	i;

	// if (pthread_create(&p_attr->monitor_thread, NULL, &monitor, p_attr) != 0)
	// 	err_message("Failed to create monitor thread\n", -1);
	for (i = 0; i < p_attr->nbr_of_philo; ++i)
	{
		if (pthread_create(&p_attr->attr[i].p_thread, NULL, philo_routine,
				&p_attr->attr[i]) != 0)
			err_message("Failed to create philosopher thread\n", -1);
	}
	// if (pthread_join(p_attr->monitor_thread, NULL) != 0)
	// 	err_message("Failed to join monitor thread\n", -1);
	for (i = 0; i < p_attr->nbr_of_philo; ++i)
	{
		if (pthread_join(p_attr->attr[i].p_thread, NULL) != 0)
			err_message("Failed to join philosopher thread\n", -1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_attr p_attr;
	int args[ac - 1];

	if (ac < 5 || ac > 6)
		err_message("Error: In valid number of arguments\n", 1);
	if (!args_handling(ac, av, args))
		err_message("Error: Invalid arguments\n", 1);
	init_shared_data(ac, args, &p_attr);
	init_philo(&p_attr);
	if (init_mutexes(&p_attr) != 0)
	{
		free(p_attr.attr);
		err_message("Failed to create forks mutexes\n", 1);
	}
	if (create_threads(&p_attr) != 0)
	{
		destroy_and_free(&p_attr);
		err_message("Failed to create threads\n", 1);
	}
	destroy_and_free(&p_attr);
	return 0;
}
