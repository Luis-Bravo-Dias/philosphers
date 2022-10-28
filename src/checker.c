/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:04:17 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/28 11:40:37 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_limit(t_status *status)
{
	int	i;

	i = 0;
	while (i < status->philo->number_of_philosophers
		&& status->philo->number_of_times_each_philosopher_must_eat != -1
		&& status[i].eat_count
		>= status->philo->number_of_times_each_philosopher_must_eat)
		i++;
	if (i == status->philo->number_of_philosophers)
	{
		printf("%sAll eat%s\n", BGREEN, NC);
		status->philo->death = 1;
		pthread_mutex_unlock(&status->philo->died);
		return (1);
	}
	return (0);
}

void	check_death(t_status *status)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&status->philo->died);
	while (i < status->philo->number_of_philosophers)
	{
		if (get_time() - status[i].last_eat
			>= status->philo->time_to_die && status->philo->death != 1)
		{
			printf("%s%lld %d died%s\n", RED,
				get_time() - status[i].philo->start_time, status[i].id, NC);
			status->philo->death = 1;
			pthread_mutex_unlock(&status->philo->died);
			return ;
		}
		if (check_limit(status))
			return ;
		i++;
	}
	pthread_mutex_unlock(&status->philo->died);
}

	// while (i < status->philo->number_of_philosophers)
	// {
	// 	// printf("eat count = %d %d\n", status[i].eat_count, status[i].id);
	// 	if (status->philo->number_of_times_each_philosopher_must_eat != -1)
	// 	{
	// 		if (status[i].eat_count
		// < status->philo->number_of_times_each_philosopher_must_eat)
	// 			return (0);
	// 	}
	// 	printf("checking ... \n");
	// 	i++;
	// }
	// if (i == status->philo->number_of_philosophers)
	// 	return (1);