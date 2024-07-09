/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:09 by hipham            #+#    #+#             */
/*   Updated: 2024/07/05 20:20:43 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 250

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define QUIT_COLOR "\033[0m"

typedef struct p_philo_info
{
	int				nbr_of_philo;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	int				nbr_of_meals;

}					t_philo_info;

typedef struct p_philo_attr
{
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	waiter;
}					t_philo_mtx;

typedef struct p_philo
{
	int				philo_id;
	int				done_eating;
	int				meals_eaten;
	int				is_dead;
	long			start;
	long			last_meal;
	pthread_t		p_thread;
	pthread_t		monitor;
	pthread_mutex_t	*fork_mutexes;
	t_philo_info	itable;
	t_philo_mtx		mtx;

}					t_philo;


// agrs_handling.c
int					args_handling(int ac, char **av, int *args);
int					str_arg_handling(char *s);
int					ft_atoi(const char *str);
int					ft_isspace(int c);
int					ft_isdigit(int x);

// philo.c
void allocate_threads(pthread_t monitor, pthread_t *philo, int nbr_of_philo);
void	*fork_mutexes(t_philo *attr);
int create_threads(t_philo *ph, int nbr_of_philos);

// philo_routine.c
void	*philo_routine(void *arg);
void	eat(t_philo *ph);
void	return_message(char *str, t_philo *attr);
void destroy_and_free(t_philo *ph);

// philo_utils.c
void	err_message(int err);
int ft_free(void *ptr);
long	get_time_now();
long	timestamp_ms(t_philo *attr);

// monitor.c
void	*monitor(void *agr);
void	check_death(t_philo *attr);

//init.c
void get_philo_info(t_philo *ph, int *args, int ac);
void init_philos(t_philo *ph);
void init_mutexes(t_philo_mtx ph);