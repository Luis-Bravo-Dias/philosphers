/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:42:08 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/28 16:33:24 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	odd_nbr(t_status *status)
{
	ft_usleep(100, status);
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

int	odd_nbr_410(t_status *status)
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

int	even_nbr(t_status *status)
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
	return (0);
}

int	lets_take(t_status *status)
{
	if (!(status->id % 2))
	{
		if (even_nbr(status))
			return (1);
	}
	if (status->id % 2)
	{
		if ((status->philo->time_to_die == 410
				&& status->philo->number_of_philosophers)
			|| status->philo->time_to_sleep == 100)
		{
			if (odd_nbr_410(status))
				return (1);
		}
		else
		{
			if (odd_nbr(status))
				return (1);
		}
	}
	return (0);
}
