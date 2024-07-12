/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:15:53 by hipham            #+#    #+#             */
/*   Updated: 2024/07/12 18:57:47 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	init_philo(t_philo_attr *ptr)
{
	int	i;

	ptr->attr = malloc(ptr->nbr_of_philo * sizeof(t_philo));
	if (ptr->attr == NULL)
	{
		printf("Failed to allocate memory for philosophers\n");
		return ;
	}
	i = -1;
	while (++i < ptr->nbr_of_philo)
	{
		ptr->attr[i].philo_id = i + 1;
		ptr->attr[i].done_eating = 0;
		ptr->attr[i].meals_eaten = 0;
		ptr->attr[i].is_dead = &ptr->stop_status;
		ptr->attr[i].last_meal = get_time_now();
		ptr->attr[i].shared_attr = ptr;
	}
}

void	init_shared_data(int ac, int *args, t_philo_attr *ptr)
{
	ptr->stop_status = 1;
	ptr->nbr_of_philo = args[0];
	ptr->time_to_die = args[1];
	ptr->time_to_eat = args[2];
	ptr->time_to_sleep = args[3];
	ptr->start = get_time_now();
	ptr->ready_to_start = 0;
	if (ac == 6)
		ptr->nbr_of_meals = args[4];
	else
		ptr->nbr_of_meals = -1;
}

int	init_mutexes(t_philo_attr *p_attr)
{
	int	i;

	p_attr->fork_mutexes = malloc(p_attr->nbr_of_philo
			* sizeof(pthread_mutex_t));
	if (p_attr->fork_mutexes == NULL)
		err_message("Failed to allocate memory for fork mutexes\n", -1);
	i = -1;
	while (++i < p_attr->nbr_of_philo)
	{
		if (pthread_mutex_init(&p_attr->fork_mutexes[i], NULL) != 0)
			err_message("Failed to init forks' mutexes\n", -1);
	}
	if (pthread_mutex_init(&p_attr->death_mutex, NULL) != 0)
		err_message("Failed to init death mutex\n", -1);
	if (pthread_mutex_init(&p_attr->write_mutex, NULL) != 0)
		err_message("Failed to init write mutex\n", -1);
	if (pthread_mutex_init(&p_attr->meal_mutex, NULL) != 0)
		err_message("Failed to init meal mutex\n", -1);
	return (0);
}
