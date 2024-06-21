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

typedef struct p_struct
{
    int         *data;
}               t_philo;

//agrs_handling.c
int args_handling(int ac, char **av);
int	str_arg_handling(char *s);

//philo.c

//philo_utils.c
int	ft_atoi(const char *str);
int	ft_isspace(int c);
int	ft_isdigit(int x);