/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:11:36 by hipham            #+#    #+#             */
/*   Updated: 2024/07/04 19:41:46 by hipham           ###   ########.fr       */
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

int	check_death(t_philo *attr)
{
	long	time_since_last_meal;
	int		i;

	i = -1;
	while (++i < attr->nbr_of_philo)
	{
		pthread_mutex_lock(&attr->death_mutex);
		time_since_last_meal = get_time_now() - attr[i].last_meal;
		if (time_since_last_meal > attr->time_to_die
			&& attr[i].done_eating == 0)
		{
			attr[i].is_dead = 0;
			return_message("has die\n", attr, i + 1);
			pthread_mutex_unlock(&attr->death_mutex);
			return 1;
		}
		pthread_mutex_unlock(&attr->death_mutex);
	}
	return 0;
}

void destroy_and_free(t_philo_attr *p_attr)
{
	int i;

	i = -1;
	while (++i < p_attr->attr->nbr_of_philo)
		pthread_mutex_destroy(&p_attr->attr->fork_mutexes[i]);
	pthread_mutex_destroy(&p_attr->attr->death_mutex);
	pthread_mutex_destroy(&p_attr->attr->write_mutex);
	pthread_mutex_destroy(&p_attr->attr->meal_mutex);
	pthread_mutex_destroy(&p_attr->attr->waiter);
	free(p_attr->attr->fork_mutexes);
	free(p_attr->attr->p_thread);
	// free(p_attr->monitor_thread);
}

void	return_message(char *str, t_philo *attr, int id)
{
	pthread_mutex_lock(&attr->write_mutex);
	printf("%li %i %s", timestamp_ms(attr), id, str);
	pthread_mutex_unlock(&attr->write_mutex);
}

void	eat(t_philo *attr, int id)
{
	int	left;
	int	right;

	left = id - 1;
	right = id % attr->nbr_of_philo;

	pthread_mutex_lock(&attr->waiter);
	pthread_mutex_lock(&attr->fork_mutexes[left]);
	return_message(GREEN" has taken l-fork\n"QUIT_COLOR, attr, id);
	pthread_mutex_lock(&attr->fork_mutexes[right]);
	return_message(GREEN"has taken r-fork\n"QUIT_COLOR, attr, id);
	pthread_mutex_unlock(&attr->waiter);
	return_message(CYAN"is eating\n"QUIT_COLOR, attr, id);
	usleep(attr->time_to_eat * 1000);
	pthread_mutex_lock(&attr->meal_mutex);
	attr[id - 1].last_meal = get_time_now();
	attr[id - 1].done_eating = 1;
	attr[id - 1].meals_eaten++;
	pthread_mutex_unlock(&attr->meal_mutex);
	pthread_mutex_unlock(&attr->fork_mutexes[right]);
	pthread_mutex_unlock(&attr->fork_mutexes[left]);
}

void	*philo_routine(void *arg)
{
	t_philo_attr	*p_attr;

	p_attr = (t_philo_attr *)arg;
	while (1)
	{
		if (p_attr->attr->nbr_of_meals != -1)
		{
			if (p_attr->attr[p_attr->philo_id - 1].meals_eaten >= p_attr->attr->nbr_of_meals)
				break ;
		}
		eat(p_attr->attr, p_attr->philo_id);
		return_message(RED"is sleeping\n"QUIT_COLOR, p_attr->attr, p_attr->philo_id);
		usleep(p_attr->attr->time_to_sleep * 1000);
		return_message(PURPLE"is thinking\n"QUIT_COLOR, p_attr->attr, p_attr->philo_id);
		if (check_death(p_attr->attr) && p_attr->attr[p_attr->philo_id - 1].is_dead == 0)
			break ;
	}
	// printf("philo[%i] have eaten %i meals\n", p_attr->philo_id, p_attr->attr[p_attr->philo_id - 1].meals_eaten);
	return (arg);
}
