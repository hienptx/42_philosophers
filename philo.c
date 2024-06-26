/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:04 by hipham            #+#    #+#             */
/*   Updated: 2024/06/26 18:25:15 by hipham           ###   ########.fr       */
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
	// printf("%li ", ret);
	return (ret);
}

// int go_eat(t_philo *attr)
// {
// 	int eat_status;

// 	eat_status = 0;
// }

// void	*philo_routine(void *arg)
// {
// 	t_philo *attr;
// 	int fork_count;
// 	int i;
	
// 	i = 0;
// 	fork_count = 2;
// 	attr = (t_philo *)arg;
// 	while (fork_count-- > 0)
// 	{
// 		pthread_mutex_unlock(&attr->mutex);
// 		printf("%li ", timestamp_ms(attr));
// 		printf("%i ", *attr->philo_id);
// 		printf("has taken a fork\n");
// 		// go_eat()
// 		pthread_mutex_lock(&attr->mutex);
// 	}
// 	return (NULL);
// }

void *create_fork(void *arg)
{
	t_philo_attr *attr;
	// t_philo_attr *ptr;

	attr = (t_philo_attr *)arg;
	pthread_mutex_lock(&attr->attr->mutex);
	attr->attr->fork_id = malloc(attr->attr->nbr_of_philo * sizeof(int)); // FREE
	if (attr->attr->fork_id == NULL)
		return (NULL);
	printf("Philo_id = %i ", attr->philo_id);
	attr->attr->fork_id[attr->philo_id - 1] = attr->philo_id;
	printf("Fork_id = %i \n", attr->attr->fork_id[attr->philo_id - 1]);
	pthread_mutex_unlock(&attr->attr->mutex);
	return (NULL);
}

void	*thread_philo(t_philo *attr)
{
	int 		i;
	t_philo_attr *p_attr;

	i = 0;
	attr->p_thread = malloc(attr->nbr_of_philo * sizeof(pthread_t));
	if (attr->p_thread == NULL)
		return (NULL);
	p_attr = malloc(attr->nbr_of_philo * sizeof(t_philo_attr));
	if (p_attr == NULL)
	{
		free(attr->p_thread);
		return (NULL);
	}
	while (i < attr->nbr_of_philo)
	{
		p_attr[i].philo_id = i + 1;
		p_attr[i].attr = attr;
		if (pthread_create(&attr->p_thread[i], NULL, create_fork, (void *)&p_attr[i]) != 0)
		{
			free(attr->p_thread);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < attr->nbr_of_philo)
	{
		printf("%i\n", p_attr[i].philo_id);
		if (pthread_join(attr->p_thread[i], NULL) != 0)
		{
			free(attr->p_thread);
			return (NULL);
		}
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
	pthread_mutex_init(&attr.mutex, NULL);
	gettimeofday(&attr.start, NULL);
	thread_philo(&attr);
	pthread_mutex_destroy(&attr.mutex);
	return (0);
}

// print arguments value
// for(int x = 0; x < ac - 1; x++)
//     printf("val = %i\n", args[x]);
