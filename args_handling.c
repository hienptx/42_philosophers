/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:39 by hipham            #+#    #+#             */
/*   Updated: 2024/06/23 14:48:42 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//av[1] number of philosophers = number of forks
//av[2] time to die (miliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
//av[3] time to eat (miliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
//av[4] time to sleep (miliseconds):The time a philosopher will spend sleeping.
//av[5] number of times each philosophers must eat (optional): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

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
