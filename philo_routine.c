/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:11:36 by hipham            #+#    #+#             */
/*   Updated: 2024/07/10 19:56:08 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	return_message(char *str, t_philo_attr *philo, int id)
{
	long	time_stamp;

	time_stamp = get_time_now() - philo->start;
	printf("%li %i %s", time_stamp, id, str);
}

void	sleeping(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->shared_attr->write_mutex);
	return_message(RED " is sleeping\n" QUIT_COLOR, philo->shared_attr, id);
	pthread_mutex_unlock(&philo->shared_attr->write_mutex);
	usleep(philo->shared_attr->time_to_sleep * 1000);
}

void	thinking(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->shared_attr->write_mutex);
	return_message(PURPLE " is thinking\n" QUIT_COLOR, philo->shared_attr, id);
	pthread_mutex_unlock(&philo->shared_attr->write_mutex);
}

void	eating(t_philo *attr, int left, int right, int id)
{
	// printf("id = %i, left = %i, right = %i \n", id, left, right);
	pthread_mutex_lock(&attr->shared_attr->fork_mutexes[right]);
	pthread_mutex_lock(&attr->shared_attr->fork_mutexes[left]);

	pthread_mutex_lock(&attr->shared_attr->write_mutex);
	return_message(GREEN " has taken right fork\n" QUIT_COLOR,
		attr->shared_attr, id);
	return_message(GREEN " has taken left fork\n" QUIT_COLOR, attr->shared_attr,
		id);
	attr->done_eating = 1;
	return_message(CYAN " is eating\n" QUIT_COLOR, attr->shared_attr, id);
	attr->meals_eaten++;
	attr->last_meal = get_time_now();
	pthread_mutex_unlock(&attr->shared_attr->write_mutex);

	// pthread_mutex_lock(&attr->shared_attr->meal_mutex);
	// pthread_mutex_unlock(&attr->shared_attr->meal_mutex);

	usleep(attr->shared_attr->time_to_eat * 1000);
	attr->done_eating = 0;
	pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[left]);
	pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[right]);
}
