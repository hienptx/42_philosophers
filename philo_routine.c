/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:11:36 by hipham            #+#    #+#             */
/*   Updated: 2024/07/01 19:57:26 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int if_dead(t_philo_attr *p_attr)
{
    int is_dead;

    pthread_mutex_lock(p_attr->attr->death_mutex);
    is_dead = p_attr->attr->is_dead;
    pthread_mutex_unlock(p_attr->attr->death_mutex);
    
    return is_dead;
}

void return_message(char *str, t_philo *attr, int id)
{
	pthread_mutex_lock(attr->write_mutex);
	printf("%li %i %s", timestamp_ms(attr), id, str);
	pthread_mutex_unlock(attr->write_mutex);
}

void eat(t_philo *attr, t_philo_attr *p_attr)
{
    int left;  
    int right;
	
	left = p_attr->philo_id - 1;
    right = (p_attr->philo_id % attr->nbr_of_philo);
	pthread_mutex_lock(&attr->fork_mutexes[right]);
	return_message("has taken r-fork\n", attr, p_attr->philo_id);

	if (attr->nbr_of_philo == 1) 
    {
		usleep(attr->time_to_die * 1000);
        pthread_mutex_unlock(&attr->fork_mutexes[right]);
        return ;
    }
	
	pthread_mutex_lock(&attr->fork_mutexes[left]);
	return_message(" has taken l-fork\n", attr, p_attr->philo_id);
    
	return_message("is eating\n", attr, p_attr->philo_id);
	usleep(attr->time_to_eat * 1000);
	
    pthread_mutex_lock(attr->meal_mutex);
	attr->last_meal = get_time_now();
	attr->done_eating = 1;
	attr->meals_eaten++;
	pthread_mutex_unlock(attr->meal_mutex);
    
	pthread_mutex_unlock(&attr->fork_mutexes[left]);
	pthread_mutex_unlock(&attr->fork_mutexes[right]);
}

void *philo_routine(void *arg) 
{
	t_philo_attr *p_attr;

	p_attr = (t_philo_attr *)arg;
    while (!if_dead(p_attr))
	{	
		return_message("is thinking\n", p_attr->attr, p_attr->philo_id);

        eat(p_attr->attr, p_attr);

		return_message("is sleeping\n", p_attr->attr, p_attr->philo_id);
        usleep(p_attr->attr->time_to_sleep * 1000);
	}
    return (arg);
}