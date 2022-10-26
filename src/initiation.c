/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:48:02 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/18 14:11:24 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lets_init(int ac, char **av, t_philo *ph)
{
	ph->number_of_philosophers = ft_atoi(av[1]);
	ph->time_to_die = ft_atoi(av[2]);
	ph->time_to_eat = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		ph->number_of_times_each_philosopher_must_eat = -1;
	ph->death = 0;
	ph->ac = ac;
}
