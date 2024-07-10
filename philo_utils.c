/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:15 by hipham            #+#    #+#             */
/*   Updated: 2024/07/10 19:35:50 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int		err_message(char *str, int err)
{
	printf("%s", str);		
	return (err);
}

int ft_free(void *ptr)
{
	free(ptr);
	return (0);
}

long	get_time_now()
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}
