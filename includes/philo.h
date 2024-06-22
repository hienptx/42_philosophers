/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:09 by hipham            #+#    #+#             */
/*   Updated: 2024/06/19 16:38:49 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// typedef struct p_struct
// {
//     int     nbr_of_philo;
//     int     time_to_die;
// }               t_philo;

// typedef struct timeval
// {
//     long tv_sec;
//     long tv_usec;
// }   t_time;

//agrs_handling.c
int args_handling(int ac, char **av, int *args);
int	str_arg_handling(char *s);

//philo.c

//philo_utils.c
int	ft_atoi(const char *str);
int	ft_isspace(int c);
int	ft_isdigit(int x);