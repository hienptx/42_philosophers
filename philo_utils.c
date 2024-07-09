/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:15 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 18:15:01 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	err_message(int err)
{
	if (err == 1)
		printf("Error: Arguments\n");
	if (err == 2)
		printf("Error: Invalid Arguments\n");
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

long	timestamp_ms(t_philo *attr)
{
	long			now;
	long			ret;

	now = get_time_now();;
	ret = now - attr->start;
	return (ret);
}
