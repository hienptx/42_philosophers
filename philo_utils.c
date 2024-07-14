/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:15 by hipham            #+#    #+#             */
/*   Updated: 2024/07/14 17:08:30 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	err_message(char *str, int err)
{
	printf("%s", str);
	return (err);
}

int	ft_free(void *ptr)
{
	free(ptr);
	return (0);
}

long	get_time_now(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

int	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time_now();
	while ((get_time_now() - start) < milliseconds)
		usleep(500);
	return (0);
}
