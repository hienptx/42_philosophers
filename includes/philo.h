/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:09 by hipham            #+#    #+#             */
/*   Updated: 2024/07/04 19:40:40 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 250

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define QUIT_COLOR "\033[0m"

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
	pthread_t		*p_thread;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	m_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	waiter;
}					t_philo;

typedef struct p_philo_attr
{
	int				philo_id;
	// pthread_t		monitor_thread;
	t_philo			*attr;
}					t_philo_attr;

// typedef struct s_status
// {
// 		t_philo_attr
// }

// agrs_handling.c
int					args_handling(int ac, char **av, int *args);
int					str_arg_handling(char *s);

// philo.c
int				create_threads(t_philo_attr *p_attr, t_philo *attr);
void				destroy_and_free(t_philo_attr *p_attr);
void				*fork_mutexes(t_philo *attr, t_philo_attr *p_attr);
// void				init_program(t_philo *p_attr);
void	init_philos(int ac, int *args, t_philo *ph);
// philo_routine.c
void				*philo_routine(void *agr);
void				return_message(char *str, t_philo *attr, int id);

// philo_utils.c
int					ft_atoi(const char *str);
int					ft_isspace(int c);
int					ft_isdigit(int x);
void				err_message(int err);
void				malloc_error(void *ptr);
int					ft_free(void *ptr);
long				get_time_now(void);
long				timestamp_ms(t_philo *attr);

// monitor.c
void				*monitor(void *agr);
int				check_death(t_philo *attr);
