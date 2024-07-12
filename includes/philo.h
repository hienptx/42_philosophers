/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:09 by hipham            #+#    #+#             */
/*   Updated: 2024/07/12 18:53:38 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define QUIT_COLOR "\033[0m"

typedef struct s_philo_attr
{
	pthread_t			monitor_thread;
	pthread_mutex_t		*fork_mutexes;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_of_meals;
	int					ready_to_start;
	int					stop_status;
	long				start;
	struct s_philo		*attr;
}						t_philo_attr;

typedef struct s_philo
{
	int					philo_id;
	int					done_eating;
	int					meals_eaten;
	int					*is_dead;
	long				last_meal;
	pthread_t			p_thread;
	t_philo_attr		*shared_attr;
}						t_philo;

// agrs_handling.c
int						args_handling(int ac, char **av, int *args);
int						str_arg_handling(char *s);
int						ft_atoi(const char *str);
int						ft_isspace(int c);
int						ft_isdigit(int x);

// philo.c
int						create_threads(t_philo_attr *p_attr);
void					*philo_routine(void *arg);
void					destroy_and_free(t_philo_attr *p_attr, int *args);
int						check_simulation_status(t_philo_attr *ptr);
// philo_routine.c
void					eating(t_philo *attr, int left, int right, int id);
void					thinking(t_philo *philo, int id);
void					sleeping(t_philo *philo, int id);
void					return_message(char *str, t_philo_attr *attr, int id);

// philo_utils.c
int						err_message(char *str, int err);
int						ft_free(void *ptr);
long					get_time_now(void);
int						ft_usleep(long milliseconds);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putnbr_fd(int n, int fd);
// void	ft_putchar_fd(char c, int fd);

// monitor.c
void					*monitor(void *arg);
int						check_death(t_philo_attr *attr);
int						check_all_ate(t_philo_attr *attr);

// init.c
int						init_mutexes(t_philo_attr *p_attr);
void					init_shared_data(int ac, int *args, t_philo_attr *ptr);
void					init_philo(t_philo_attr *ptr);
