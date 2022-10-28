/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:49:48 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/28 15:42:44 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
