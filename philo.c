/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/07/14 17:25:28 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

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
	int		left;
	int		right;

	philo = (t_philo *)arg;
	right = philo->philo_id - 1;
	left = philo->philo_id % philo->shared_attr->nbr_of_philo;
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (check_simulation_status(philo->shared_attr))
	{
		thinking(philo, philo->philo_id);
		eating(philo, left, right, philo->philo_id);
		sleeping(philo, philo->philo_id);
	}
	return (NULL);
}

int	create_threads(t_philo_attr *p_attr)
{
	int	i;

	if (pthread_create(&p_attr->monitor_thread, NULL, &monitor, p_attr) != 0)
		err_message("Failed to create monitor thread\n", -1);
	i = -1;
	while (++i < p_attr->nbr_of_philo)
	{
		if (pthread_create(&p_attr->attr[i].p_thread, NULL, philo_routine,
				&p_attr->attr[i]) != 0)
			err_message("Failed to create philosopher thread\n", -1);
	}
	if (pthread_join(p_attr->monitor_thread, NULL) != 0)
		err_message("Failed to join monitor thread\n", -1);
	i = -1;
	while (++i < p_attr->nbr_of_philo)
	{
		if (pthread_join(p_attr->attr[i].p_thread, NULL) != 0)
			err_message("Failed to join philosopher thread\n", -1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_attr	p_attr;
	int				*args;

	if (ac < 5 || ac > 6)
		err_message("Error: In valid number of arguments\n", 1);
	args = malloc((ac - 1) * sizeof(int));
	if (args == NULL)
		err_message("Failed to allocate int array\n", 1);
	if (!args_handling(ac, av, args))
		err_message("Error: Invalid arguments\n", 1);
	init_shared_data(ac, args, &p_attr);
	init_philo(&p_attr);
	if (init_mutexes(&p_attr) != 0)
	{
		free(args);
		free(p_attr.attr);
		err_message("Failed to create forks mutexes\n", 1);
	}
	if (create_threads(&p_attr) != 0)
	{
		destroy_and_free(&p_attr, args);
		err_message("Failed to create threads\n", 1);
	}
	destroy_and_free(&p_attr, args);
	return (0);
}

// void	simulation_start_point(t_philo_attr *philo)
// {
// 	int	i;

// 	philo->start = get_time_now();
// 	i = -1;
// 	while (++i < philo->nbr_of_philo)
// 		philo->attr[i].last_meal = philo->start;
// }