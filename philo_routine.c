/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:11:36 by hipham            #+#    #+#             */
/*   Updated: 2024/07/14 17:30:41 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	return_message(char *str, t_philo_attr *philo, int id)
{
	pthread_mutex_lock(&philo->write_mutex);
	if (philo->stop_status != 0)
		printf("%li %i %s", get_time_now() - philo->start, id, str);
	pthread_mutex_unlock(&philo->write_mutex);
}

void	sleeping(t_philo *philo, int id)
{
	return_message(RED " is sleeping\n" QUIT_COLOR, philo->shared_attr, id);
	ft_usleep(philo->shared_attr->time_to_sleep);
}

void	thinking(t_philo *philo, int id)
{
	return_message(PURPLE " is thinking\n" QUIT_COLOR, philo->shared_attr, id);
}

void	single_philo(t_philo *attr, int left)
{
	usleep(attr->shared_attr->time_to_die * 1000);
	attr->shared_attr->stop_status = 0;
	pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[left]);
}

// Fork debug: printf("philo[%i] - l_fork[%i] - r_fork[%i]\n", id, left, right);

void	eating(t_philo *attr, int left, int right, int id)
{
	pthread_mutex_lock(&attr->shared_attr->fork_mutexes[left]);
	return_message(GREEN " has taken a fork\n" QUIT_COLOR, attr->shared_attr,
		id);
	if (attr->shared_attr->nbr_of_philo == 1)
		single_philo(attr, left);
	else
	{
		pthread_mutex_lock(&attr->shared_attr->fork_mutexes[right]);
		return_message(GREEN " has taken a fork\n" QUIT_COLOR,
			attr->shared_attr, id);
		pthread_mutex_lock(&attr->shared_attr->meal_mutex);
		attr->last_meal = get_time_now();
		attr->done_eating = 1;
		pthread_mutex_unlock(&attr->shared_attr->meal_mutex);
		return_message(CYAN " is eating\n" QUIT_COLOR, attr->shared_attr, id);
		ft_usleep(attr->shared_attr->time_to_eat);
		pthread_mutex_lock(&attr->shared_attr->meal_mutex);
		attr->meals_eaten++;
		attr->done_eating = 0;
		pthread_mutex_unlock(&attr->shared_attr->meal_mutex);
		pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[left]);
		pthread_mutex_unlock(&attr->shared_attr->fork_mutexes[right]);
	}
}
