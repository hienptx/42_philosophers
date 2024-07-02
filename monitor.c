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

int check_death(t_philo *attr)
{
    long time_since_last_meal;
    int i;

    i = -1;
    while (++i < attr->nbr_of_philo)
    {
        pthread_mutex_lock(attr->death_mutex);
        time_since_last_meal = get_time_now() - attr[i].last_meal;
        if (time_since_last_meal > attr->time_to_die && attr[i].done_eating == 0)
        {
            attr[i].is_dead = 1;
            return_message("has die\n", attr, i + 1);
            pthread_mutex_unlock(attr->death_mutex);
            return (1);
        }
        pthread_mutex_unlock(attr->death_mutex);
    }
    return (0);
}

void *monitor(void *agr)
{
    t_philo_attr    *p_attr;
    
    p_attr = (t_philo_attr *)agr;
    while(1)
    {
        if (check_death(p_attr->attr) == 1)
            destroy_and_free(p_attr);
        break ;
    }
    return (agr);
}
