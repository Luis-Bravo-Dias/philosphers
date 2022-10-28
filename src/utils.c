/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:31:45 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/28 11:54:07 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	size_t	n;
	size_t	result;
	size_t	sign;

	n = 0;
	result = 0;
	sign = 1;
	if (!str[0] || !str)
		return (0);
	while ((str[n] >= 9 && str[n] <= 13) || str[n] == 32)
		n++;
	if (str[n] == '-' || str[n] == '+')
		if (str[n++] == '-')
			sign *= -1;
	if (str[n] == '-' || str[n] == '+')
		return (0);
	while (str[n] >= '0' && str[n] <= '9')
	{
		result *= 10;
		result += str[n] - '0';
		n++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	lets_print(t_status *status, char *msg)
{
	pthread_mutex_lock(&status->philo->died);
	if (status->philo->death == 1)
	{
		pthread_mutex_unlock(&status->philo->died);
		return (1);
	}
	pthread_mutex_unlock(&status->philo->died);
	printf("%lld %d %s%s\n", get_time() - status->philo->start_time,
		status->id, msg, NC);
	return (0);
}

int	ft_usleep(long long time, t_status *status)
{
	long long	start;
	long long	finish;

	start = get_time();
	finish = start + time;
	while (get_time() < finish)
	{
		pthread_mutex_lock(&status->philo->died);
		if (status->philo->death == 1)
		{
			pthread_mutex_unlock(&status->philo->died);
			return (1);
		}
		pthread_mutex_unlock(&status->philo->died);
		if ((get_time() - start) >= time)
			break ;
		usleep(50);
	}
	return (0);
}
