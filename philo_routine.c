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
	pthread_mutex_lock(p_attr->attr->death_mutex);
	if (p_attr->attr->is_dead == 1)
	{
		pthread_mutex_unlock(p_attr->attr->death_mutex);
		return(0);
	}
	pthread_mutex_unlock(p_attr->attr->death_mutex);
	return (1);
}

void return_message(char *str, t_philo *attr, t_philo_attr *p_attr)
{
	// pthread_mutex_lock(attr->write_mutex);
	printf("%li %i %s", timestamp_ms(attr), p_attr->philo_id, str);
	// pthread_mutex_unlock(attr->write_mutex);
}

void eat(t_philo *p_attr, t_philo_attr *attr)
{
    int left;  
    int right;
	
	left = attr->philo_id - 1;
    right = (attr->philo_id % p_attr->nbr_of_philo);
	pthread_mutex_lock(&p_attr->fork_mutexes[right]);
	return_message("has taken r-fork\n", p_attr, attr);

	if (p_attr->nbr_of_philo == 1) 
    {
		usleep(p_attr->time_to_die * 1000);
        pthread_mutex_unlock(&p_attr->fork_mutexes[right]);
        return ;
    }
	
	pthread_mutex_lock(&p_attr->fork_mutexes[left]);
	return_message(" has taken l-fork\n", p_attr, attr);
    
	return_message("is eating\n", p_attr, attr);
	usleep(p_attr->time_to_eat * 1000);
	
    pthread_mutex_lock(p_attr->meal_mutex);
	p_attr->last_meal = get_time_now();
	p_attr->done_eating = 1;
	p_attr->meals_eaten++;
	pthread_mutex_unlock(p_attr->meal_mutex);
    
	pthread_mutex_unlock(&p_attr->fork_mutexes[left]);
	pthread_mutex_unlock(&p_attr->fork_mutexes[right]);
}

void *philo_routine(void *arg) 
{
	t_philo_attr *p_attr;

	p_attr = (t_philo_attr *)arg;
    while (!if_dead(p_attr))
	{	
		return_message("is thinking\n", p_attr->attr, p_attr);

        eat(p_attr->attr, p_attr);

		return_message("is sleeping\n", p_attr->attr, p_attr);
        usleep(p_attr->attr->time_to_sleep * 1000);
	}
    return (arg);
}