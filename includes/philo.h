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

typedef struct p_philo
{
	int				nbr_of_philo;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	int				nbr_of_meals;
	int				done_eating;
	int				meals_eaten;
	int				is_dead;
	long			start;
	long			last_meal;
	pthread_mutex_t *meal_mutex;
	pthread_mutex_t *death_mutex;
	pthread_mutex_t *write_mutex;
	pthread_t		*p_thread;
	pthread_mutex_t	*fork_mutexes;
}					t_philo;

typedef struct p_philo_attr
{
	int				philo_id;
	t_philo			*attr;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t death_mutex;
	pthread_mutex_t write_mutex;
}					t_philo_attr;

// typedef struct s_status
// {
// 	t_philo_attr 
// }

// agrs_handling.c
int					args_handling(int ac, char **av, int *args);
int					str_arg_handling(char *s);

// philo.c
void				*thread_philo(t_philo *attr);
void				initialize_forks(t_philo *attr);
void				initialize_threads(t_philo_attr *p_attr, t_philo *attr);
void 				info_struct(int ac, int *args, t_philo *attr);
long				timestamp_ms(t_philo *attr);
long				get_time_now();

// philo_routine.c
void				*philo_routine(void *agr);

// philo_utils.c
int					ft_atoi(const char *str);
int					ft_isspace(int c);
int					ft_isdigit(int x);
void				err_message(int err);
void				*malloc_error(void *ptr);
void 				*ft_free(void *ptr);
