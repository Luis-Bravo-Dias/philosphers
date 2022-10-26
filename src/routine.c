/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:49:48 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/26 12:58:00 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	odd_nbr(t_status *status)
{
	usleep(100);
	pthread_mutex_lock(&status->forks_r);
	if (lets_print(status, "\e[33mhas taken a fork"))
	{
		pthread_mutex_unlock(&status->forks_r);
		return (1);
	}
	if (status->philo->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&status->forks_r);
		return (1);
	}
	pthread_mutex_lock(status->forks_l);
	if (lets_print(status, "\e[33mhas taken a fork"))
	{
		pthread_mutex_unlock(&status->forks_r);
		pthread_mutex_unlock(status->forks_l);
		return (1);
	}
	return (0);
}

int	lets_take(t_status *status)
{
	if (!(status->id % 2))
	{
		pthread_mutex_lock(status->forks_l);
		if (lets_print(status, "\e[33mhas taken a fork"))
		{
			pthread_mutex_unlock(status->forks_l);
			return (1);
		}
		pthread_mutex_lock(&status->forks_r);
		if (lets_print(status, "\e[33mhas taken a fork"))
		{
			pthread_mutex_unlock(status->forks_l);
			pthread_mutex_unlock(&status->forks_r);
			return (1);
		}
	}
	else
	{
		if (odd_nbr(status))
			return (1);
	}
	return (0);
}

void	counter(t_status *status)
{
	pthread_mutex_lock(&status->philo->died);
	status->last_eat = get_time();
	status->eat_count++;
	pthread_mutex_unlock(&status->philo->died);
	ft_usleep(status->philo->time_to_eat, status);
}

// void	unlock_odd(t_status *status)
// {
// 	pthread_mutex_unlock(&status->forks_r);
// 	pthread_mutex_unlock(status->forks_l);
// }

int	lets_eat(t_status *status)
{
	if (lets_print(status, "\e[32mis eating"))
	{
		if (!(status->id % 2))
		{
			pthread_mutex_unlock(status->forks_l);
			pthread_mutex_unlock(&status->forks_r);
		}
		else
		{
			pthread_mutex_unlock(&status->forks_r);
			pthread_mutex_unlock(status->forks_l);
		}
		return (1);
	}
	return (0);
}

void	let_go(t_status *status)
{
	pthread_mutex_unlock(&status->forks_r);
	pthread_mutex_unlock(status->forks_l);
}
