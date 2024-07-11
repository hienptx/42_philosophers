/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:48:15 by hipham            #+#    #+#             */
/*   Updated: 2024/07/11 19:24:20 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	err_message(char *str, int err)
{
	printf("%s", str);
	return (err);
}

int	ft_free(void *ptr)
{
	free(ptr);
	return (0);
}

long	get_time_now(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	while (*s != '\0')
// 	{
// 		write(fd, s, 1);
// 		s++;
// 	}
// }

// void	ft_putchar_fd(char c, int fd)
// {
// 	const void	*a;

// 	a = &c;
// 	write(fd, a, 1);
// }

// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (n == -2147483648)
// 	{
// 		write(fd, "-2147483648", 11);
// 		return ;
// 	}
// 	if (n == 0)
// 	{
// 		write(fd, "0", 1);
// 		return ;
// 	}
// 	if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		n = -n;
// 	}
// 	if (n >= 10)
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 	}
// 	ft_putchar_fd(n % 10 + '0', fd);
// }
