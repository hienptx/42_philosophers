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