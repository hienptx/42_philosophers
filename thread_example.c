/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:47:13 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 17:48:18 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_WORKERS 3
#define NUM_INCREMENTS 10

// Struct to encapsulate shared data and mutex
typedef struct
{
	int				shared_variable;
	pthread_mutex_t	lock;
}					SharedData;

// Worker thread function
void	*worker_thread(void *arg)
{
	SharedData	*data;

	data = (SharedData *)arg;
	for (int i = 0; i < NUM_INCREMENTS; ++i)
	{
		usleep(100000); // Simulate work by sleeping (100ms)
		pthread_mutex_lock(&data->lock);
		data->shared_variable++;
		printf("Worker %d: incremented shared_variable to %d\n", pthread_self(),
			data->shared_variable);
		pthread_mutex_unlock(&data->lock);
	}
	return (NULL);
}

// Monitor thread function
void	*monitor_thread(void *arg)
{
	SharedData	*data;

	data = (SharedData *)arg;
	while (1)
	{
		usleep(500000); // Monitor at intervals (500ms)
		pthread_mutex_lock(&data->lock);
		printf("Monitor: shared_variable is %d\n", data->shared_variable);
		if (data->shared_variable >= NUM_WORKERS * NUM_INCREMENTS)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	workers[NUM_WORKERS];
	pthread_t	monitor;
	SharedData	data;

	// Initialize the shared data
	data.shared_variable = 0;
	pthread_mutex_init(&data.lock, NULL);
	// Create worker threads
	for (int i = 0; i < NUM_WORKERS; ++i)
	{
		if (pthread_create(&workers[i], NULL, worker_thread, &data) != 0)
		{
			perror("Failed to create worker thread");
			return (1);
		}
	}
	// Create monitor thread
	if (pthread_create(&monitor, NULL, monitor_thread, &data) != 0)
	{
		perror("Failed to create monitor thread");
		return (1);
	}
	// Wait for all worker threads to finish
	for (int i = 0; i < NUM_WORKERS; ++i)
	{
		pthread_join(workers[i], NULL);
	}
	// Wait for the monitor thread to finish
	pthread_join(monitor, NULL);
	// Destroy the mutex
	pthread_mutex_destroy(&data.lock);
	return (0);
}
