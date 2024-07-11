/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:02:58 by hipham            #+#    #+#             */
/*   Updated: 2024/07/01 20:25:12 by hipham           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ate(t_philo_attr *attr)
{
	int	all_ate;
	int	i;

	i = -1;
	all_ate = 0;
	while (++i < attr->nbr_of_philo)
	{
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
		return (1);
	}
	return (0);
}

int	check_death(t_philo_attr *attr)
{
	int	i;
	int	since_last_meal;

	i = -1;
	while (++i < attr->nbr_of_philo)
	{
		pthread_mutex_lock(&attr->death_mutex);
		since_last_meal = get_time_now() - attr->attr[i].last_meal;
		if (since_last_meal >= attr->time_to_die && !attr->attr[i].done_eating)
		{
			return_message(" died\n", attr, attr->attr[i].philo_id);
			attr->stop_status = 0;
			pthread_mutex_unlock(&attr->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&attr->death_mutex);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo_attr	*attr;

	attr = (t_philo_attr *)arg;
	while (check_simulation_status(attr))
	{
		if (check_death(attr) == 1 || check_all_ate(attr) == 1)
			break ;
	}
	return (NULL);
}
