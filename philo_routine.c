/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:11:36 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 20:23:07 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// int	if_dead(t_philo_attr *p_attr)
// {
// 	int	is_dead;

// 	is_dead = 1;
// 	// pthread_mutex_lock(p_attr->attr[id].death_mutex);
// 	is_dead = p_attr->attr->is_dead;
// 	// pthread_mutex_unlock(p_attr->attr[id].death_mutex);
// 	return (is_dead);
// }

void destroy_and_free(t_philo *ph)
{
	int i;

	i = -1;
	while (++i < ph->itable.nbr_of_philo)
		pthread_mutex_destroy(&ph->fork_mutexes[i]);
	pthread_mutex_destroy(&ph->mtx.death_mutex);
	pthread_mutex_destroy(&ph->mtx.write_mutex);
	pthread_mutex_destroy(&ph->mtx.meal_mutex);
	pthread_mutex_destroy(&ph->mtx.waiter);
	free(ph->fork_mutexes);
	free(ph->p_thread);
	free(ph->monitor);
}

void	return_message(char *str, t_philo *attr)
{
	pthread_mutex_lock(&attr->mtx.write_mutex);
	printf("%li %i %s", timestamp_ms(attr), attr->philo_id, str);
	pthread_mutex_unlock(&attr->mtx.write_mutex);
}

void	eat(t_philo *ph)
{
	int	left;
	int	right;

	left = ph->philo_id - 1;
	right = ph->philo_id % ph->itable.nbr_of_philo;

	if (ph->philo_id % 2 == 0)
		usleep(500);

	pthread_mutex_lock(&ph->mtx.waiter);
	
	pthread_mutex_lock(&ph->fork_mutexes[left]);
	return_message(GREEN" has taken l-fork\n"QUIT_COLOR, ph);
	pthread_mutex_lock(&ph->fork_mutexes[right]);
	return_message(GREEN"has taken r-fork\n"QUIT_COLOR, ph);
	
	pthread_mutex_unlock(&ph->mtx.waiter);

	return_message(CYAN"is eating\n"QUIT_COLOR, ph);
	usleep(ph->itable.time_to_eat * 1000);
	
	pthread_mutex_lock(&ph->mtx.meal_mutex);
	ph[ph->philo_id - 1].last_meal = get_time_now();
	ph[ph->philo_id - 1].done_eating = 1;
	ph[ph->philo_id - 1].meals_eaten++;
	pthread_mutex_unlock(&ph->mtx.meal_mutex);
	
	// check_death(ph);
	pthread_mutex_unlock(&ph->fork_mutexes[right]);
	pthread_mutex_unlock(&ph->fork_mutexes[left]);
}

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (ph->itable.nbr_of_meals != -1)
		{
			if (ph[ph->philo_id - 1].meals_eaten >= ph->itable.nbr_of_meals)
				break ;
		}
		eat(ph);
		return_message(RED"is sleeping\n"QUIT_COLOR, ph);
		usleep(ph->itable.time_to_sleep * 1000);
		return_message(PURPLE"is thinking\n"QUIT_COLOR, ph);
		// if (check_death(p_attr->attr) && p_attr->attr[p_attr->philo_id - 1].is_dead == 0)
		// 	break ;
	}
	// printf("philo[%i] have eaten %i meals\n", attr->philo_id, attr[attr->philo_id - 1].meals_eaten);
	return (arg);
}
