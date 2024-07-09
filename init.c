/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:15:53 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 20:24:06 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void init_mutexes(t_philo_mtx ph)
{
	pthread_mutex_init(&ph.death_mutex, NULL);
	pthread_mutex_init(&ph.write_mutex, NULL);
	pthread_mutex_init(&ph.meal_mutex, NULL);
	pthread_mutex_init(&ph.waiter, NULL);
}

void init_philos(t_philo *ph)
{
	int i;

	i = -1;
	while (++i < ph->itable.nbr_of_philo)
	{
		ph[i].philo_id = i + 1;
		ph[i].done_eating = 0;
		ph[i].meals_eaten = 0;
		ph[i].is_dead = 1;
		ph[i].last_meal = get_time_now();
	}
	ph->start = get_time_now();
}

void get_philo_info(t_philo *ph, int *args, int ac)
{
	ph->itable.nbr_of_philo = args[0];
	ph->itable.time_to_die = args[1];
	ph->itable.time_to_eat = args[2];
	ph->itable.time_to_sleep = args[3];
	if (ac == 6)
		ph->itable.nbr_of_meals = args[4];
	else
		ph->itable.nbr_of_meals = -1;
}
