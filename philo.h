/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:57:17 by lleiria-          #+#    #+#             */
/*   Updated: 2022/10/26 12:59:44 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define NC		"\e[0m"
# define YELLOW	"\e[33m"
# define BYELLOW	"\e[1;33m"
# define RED		"\e[31m"
# define GREEN	"\e[32m"
# define BLUE	"\e[34m"
# define MAGENTA	"\e[35m"
# define CYAN	"\e[36m"
# define WHITE	"\e[37m"
# define BGREEN	"\e[1;32m"

typedef struct s_philo
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	long long			start_time;
	int					death;
	pthread_mutex_t		died;
	int					ac;
}	t_philo;

typedef struct s_status
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		*forks_l;
	pthread_mutex_t		forks_r;
	struct s_philo		*philo;
	int					eat_count;
	time_t				last_eat;
}	t_status;

//utils.c
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			lets_print(t_status *status, char *msg);
int			ft_usleep(long long time, t_status *status);
int			delay(t_status *status);
//initiation.c
void		lets_init(int ac, char **av, t_philo *ph);
//time.c
long long	get_time(void);
//create_threads.c
void		create_threads(t_philo *ph, t_status *status);
//checker.c
int			check_limit(t_status *status);
void		check_death(t_status *status);
//main.c
void		finish_him(t_status *status);
//rotine.c
int			lets_take(t_status *status);
int			lets_eat(t_status *status);
void		let_go(t_status *status);
void		counter(t_status *status);

#endif
