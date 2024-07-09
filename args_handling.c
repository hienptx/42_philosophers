/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:39 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 18:14:05 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//av[1] number of philosophers = number of forks
//av[2] time to die (miliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
//av[3] time to eat (miliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
//av[4] time to sleep (miliseconds):The time a philosopher will spend sleeping.
//av[5] number of times each philosophers must eat (optional): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

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

int	str_arg_handling(char *s)
{
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && ft_isspace(*s))
			s++;
		if (*s != '\0' && (*s == '-' || *s == '+'))
		{
			s++;
			if (*s == '\0')
				return (0);
		}
		if (*s != '\0' && !ft_isdigit(*s))
			return (0);
		if (*s != '\0' && ft_isdigit(*s))
		{
			while (*s != '\0' && ft_isdigit(*s))
				s++;
		}
		if (*s != '\0' && !ft_isspace(*s))
			return (0);
	}
	return (1);
}

int args_handling(int ac, char **av, int *args)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!str_arg_handling(av[i]))
            return (0);
        args[i - 1] = ft_atoi(av[i]);
        i++;
    }
    return (1);
}
