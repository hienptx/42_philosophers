/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:09 by hipham            #+#    #+#             */
/*   Updated: 2024/06/26 17:57:33 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct p_info_struct
{
	int				nbr_of_philo;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	int				nbr_of_meals;
	pthread_t		*p_thread;
	struct timeval	start;
	int				*fork_id;
	pthread_mutex_t	mutex;
}					t_philo;

typedef struct p_id_struct
{
	t_philo			*attr;
	int				philo_id;
}					t_philo_attr;

typedef struct s_status
{
	t_philo_attr 
}

// agrs_handling.c
int					args_handling(int ac, char **av, int *args);
int					str_arg_handling(char *s);

// philo.c
void 				info_struct(int ac, int *args, t_philo *attr);
void				*thread_philo(t_philo *attr);
void 				*create_fork(void *arg);
long				timestamp_ms(t_philo *attr);

// philo_routine.c
void	*philo_routine(t_philo_attr *p_attr);


// philo_utils.c
int					ft_atoi(const char *str);
int					ft_isspace(int c);
int					ft_isdigit(int x);
void				err_message(int err);
void *malloc_error(void *ptr);
void *ft_free(void *ptr);
