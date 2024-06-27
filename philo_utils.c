/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:15 by hipham            #+#    #+#             */
/*   Updated: 2024/06/26 18:10:47 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			neopo;
	int	output;

	i = 0;
	neopo = 1;
	output = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neopo = -neopo;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = (str[i] - '0') + (output * 10);
		i++;
	}
	return (output * neopo);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int x)
{
	if (!(48 <= x && x <= 57))
		return (0);
	return (1);
}

void	err_message(int err)
{
	if (err == 1)
		printf("Error: Arguments\n");
	if (err == 2)
		printf("Error: Invalid Arguments\n");
}

void *malloc_error(void *ptr)
{
	if (ptr == NULL)
		free(ptr);
	return(NULL);
}

void *ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}