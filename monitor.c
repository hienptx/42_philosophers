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

// int	count_meals(t_philo *attr, int id)
// {
// 	int	i;
// 	int		reached_meals_limit;

// 	i = -1;
// 	reached_meals_limit = 0;
// 	while (++i < attr->nbr_of_philo)
// 	{
// 		pthread_mutex_lock(&attr->meal_mutex);
// 		if (attr[i].meals_eaten >= attr->nbr_of_meals)
// 			reached_meals_limit += 1;
// 		pthread_mutex_unlock(&attr->meal_mutex);
// 	}
// 	if (reached_meals_limit == attr->nbr_of_philo)
// 	{
// 		pthread_mutex_lock(&attr->death_mutex);

// 		pthread_mutex_lock(&attr->death_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// void	check_death(t_philo *attr)
// {
// 	long	time_since_last_meal;
// 	int		i;

// 	i = -1;
// 	while (++i < attr->itable->nbr_of_philo)
// 	{
// 		pthread_mutex_lock(&attr->mtx->death_mutex);
// 		time_since_last_meal = get_time_now() - attr[i].last_meal;
// 		printf("time since last meal in eat loop = %li\n",
// 			time_since_last_meal);
// 		if (time_since_last_meal > attr->itable->time_to_die
// 			&& attr[i].done_eating == 0)
// 		{
// 			attr[i].is_dead = 0;
// 			return_message("has die\n", attr, i + 1);
// 			pthread_mutex_unlock(&attr->mtx->death_mutex);
// 		}
// 		pthread_mutex_unlock(&attr->mtx->death_mutex);
// 	}
// }

void	*monitor(void *agr)
{
	t_philo	*ph;
	long	time_since_last_meal;
	int		i;

	ph = (t_philo *)agr;
	i = -1;
	while (1)
	{
		while (++i < ph->itable.nbr_of_philo)
		{
			pthread_mutex_lock(&ph->mtx.death_mutex);
			time_since_last_meal = get_time_now() - ph[i].last_meal;
			printf("time since last meal in monitor = %li\n",
				time_since_last_meal);
			printf("done eating = %i\n", ph[i].done_eating);
			printf("meal eaten = %i\n", ph[i].meals_eaten);
			pthread_mutex_unlock(&ph->mtx.death_mutex);
			if (time_since_last_meal > ph->itable.time_to_die
				&& ph[i].done_eating == 0)
			{
				ph[i].is_dead = 0;
				return_message("has die\n", ph);
				// pthread_mutex_unlock(&ph->death_mutex);
				break ;
			}
		}
		if (ph[i].is_dead == 0)
			break ;
	}
	return (NULL);
}
