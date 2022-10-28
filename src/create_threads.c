/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:12:13 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/28 15:31:31 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mutex(t_status *status, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->number_of_philosophers)
	{
		pthread_mutex_init(&status->forks_r, NULL);
		if (i != 0)
			status[i].forks_l = &(status[i - 1].forks_r);
		else
			status[i].forks_l
				= &(status[ph->number_of_philosophers - 1].forks_r);
		i++;
	}
	pthread_mutex_init(&status->philo->died, NULL);
}

t_status	*init_thread(t_philo *ph)
{
	t_status	*status;
	int			i;

	i = 0;
	status = malloc(sizeof(t_status) * ph->number_of_philosophers);
	if (!status)
	{
		printf("Error: malloc failed\n");
		return (NULL);
	}
	while (i < ph->number_of_philosophers)
	{
		status[i].id = i + 1;
		status[i].last_eat = get_time();
		status[i].eat_count = 0;
		status[i].philo = ph;
		i++;
	}
	init_mutex(status, ph);
	return (status);
}

	// if(status->id % 2 == 0)
	// 	ft_usleep(2000, status);
	// if(!(status->id % 2 == 0) 
	// && status->id == status->philo->number_of_philosophers)
	// 	ft_usleep(500, status);
void	*routine(void *arg)
{
	t_status	*status;

	status = (t_status *)arg;
	while (1)
	{
		if (lets_take(status))
			break ;
		if (lets_eat(status))
			break ;
		counter(status);
		let_go(status);
		if (lets_print(status, "\e[34mis sleeping"))
			break ;
		ft_usleep(status->philo->time_to_sleep, status);
		if (lets_print(status, "\e[35mis thinking"))
			break ;
	}
	return (NULL);
}

void	create_threads(t_philo *ph, t_status *status)
{
	int			i;

	i = 0;
	ph->start_time = get_time();
	status = init_thread(ph);
	while (i < ph->number_of_philosophers)
	{
		pthread_create(&status[i].thread_id, NULL, &routine, &status[i]);
		i++;
	}
	while (1)
	{
		check_death(status);
		if (ph->death)
			break ;
	}
	i = -1;
	while (++i < ph->number_of_philosophers)
		pthread_join(status[i].thread_id, NULL);
	finish_him(status);
}
