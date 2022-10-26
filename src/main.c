/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:31:48 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/18 14:48:29 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_arg(int ac)
{
	if (ac < 5)
	{
		printf("Inuficient arguments!\n");
		printf("Use: ./philosophers nbr_philo time_to_die time_to_eat");
		printf(" time_to_sleep nbr_times_to_eat(optional)\n");
		return (1);
	}
	if (ac > 6)
	{
		printf("To mutch arguments!\n");
		printf("Use: ./philosophers nbr_philo time_to_die time_to_eat");
		printf(" time_to_sleep nbr_times_to_eat(optional)\n");
		return (1);
	}
	return (0);
}

int	is_zero(int ac, char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1
		|| ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1
		|| (ac == 6 && ft_atoi(av[5]) == 0))
	{
		printf("Error: invalid argument\n");
		return (1);
	}
	return (0);
}

int	check_arg_2(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("Error: invalid argument\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	if (is_zero(ac, av))
		return (1);
	return (0);
}

void	finish_him(t_status *status)
{
	int	i;

	i = 0;
	while (++i <= status->philo->number_of_philosophers)
		pthread_mutex_destroy(&status[i].forks_r);
	pthread_mutex_destroy(&status->philo->died);
	free(status);
}

int	main(int ac, char **av)
{
	t_philo		ph;
	t_status	status;

	if (check_arg(ac) || check_arg_2(ac, av))
		return (1);
	lets_init(ac, av, &ph);
	create_threads(&ph, &status);
	return (0);
}

	// i = -1;
	// while(++i < ph.number_of_philosophers)
	// 	pthread_join(status[i].thread_id, NULL);
	//while (1);