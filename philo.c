/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/06/25 19:51:03 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

// Convert to Milliseconds: The seconds (tv.tv_sec) are multiplied by 1000
// to convert to milliseconds. The microseconds (tv.tv_usec) are divided by 1000
//  to convert to milliseconds. These two values are added together to get
//  the current timestamp in milliseconds.

int	even_or_odd(int num)
{
	return (num % 2);
}

long	timestamp_ms(t_philo *attr)
{
	struct timeval	tv;
	long			start_ms;
	long			ms;
	long			ret;

	gettimeofday(&tv, NULL);
	start_ms = (attr->start.tv_sec * 1000) + (attr->start.tv_usec / 1000);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	ret = ms - start_ms;
	printf("%li ", ret);
	return (ret);
}

void	*philo_routine(void *arg)
{
	t_philo *attr;
	int fork_count;
	pthread_mutex_t	mutex;
	
	fork_count = 2;
	attr = (t_philo *)arg;
	while (fork_count-- > 0)
	{
		pthread_mutex_unlock(&mutex);
		timestamp_ms(attr);
		printf("%i ", *(attr)->philo_id);
		printf("has taken a fork\n");
		pthread_mutex_lock(&mutex);
	}
	return (NULL);
}


void	*thread_philo(t_philo *attr)
{
	pthread_t	phi_thread[attr->nbr_of_philo];
	int 		i;

	i = 1;
	while (i <= attr->nbr_of_philo)
	{
		*attr->philo_id = i;
		pthread_create(&phi_thread[i], NULL, philo_routine, (void *)attr);
		pthread_join(phi_thread[i], NULL);
		i++;
	}
	return (NULL);
}

void pass_val_to_philo_struct(int ac, int *args, t_philo *attr)
{
	attr->nbr_of_philo = args[0];
	attr->time_to_die = args[1];
	attr->time_to_eat = args[2];
	attr->time_to_sleep = args[3];
	if (ac == 6)
		attr->nbr_of_meals = args[4];

}

int	main(int ac, char **av)
{
	pthread_mutex_t	mutex;
	t_philo			attr;

	int	args[ac - 1];
	if (ac < 5 || ac > 6)
	{
		err_message(1);
		return (1);
	}
	if (!args_handling(ac, av, args))
		err_message(2);
	pass_val_to_philo_struct(ac, args, &attr);
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&attr.start, NULL);
	thread_philo(&attr);
	pthread_mutex_destroy(&mutex);
	return (0);
}

// print arguments value
// for(int x = 0; x < ac - 1; x++)
//     printf("val = %i\n", args[x]);
