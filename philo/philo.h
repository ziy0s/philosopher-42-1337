/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:39:53 by zaissi            #+#    #+#             */
/*   Updated: 2025/03/06 05:33:04 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

struct timeval start_time;
struct s_data	*data;

typedef	struct	s_philo
{
	int							id;
	int							num_eat;
	int							time_die;
	int							die;
	pthread_mutex_t				*l_fork;
	pthread_mutex_t				*r_fork;
	struct s_data				*data;
	u_int64_t					eat_time;
	// pthread_mutex_t				eat_mutex;
	pthread_t					thread;
}				t_philo;

typedef struct	s_data
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_eat;
	t_philo				*philo;
	unsigned long long	start;
	pthread_mutex_t		*forks;
}				t_data;



int		ft_atoi(const char *str);

void	error();
void    ft_exit(int i);
void    *ft_malloc(size_t size);

#endif



// Usag :
//         ./philo num_philo time_to_die time_to_eat time_to_sleep [num_of_eating]
// Args:
//         num_philo       :       the Number of philosophers [1 - 200]
//         time_to_die     :       Time to die the philo (in milliseconds) [60 - INT_MAX]
//         time_to_eat     :       Time to eat the philo (in milliseconds) [60 - INT_MAX]
//         time_to_sleep   :       Time to sleep the philo (in milliseconds) [60 - INT_MAX]
//         num_of_eating   :       Time to eating (*optional argumen*) [2 - INT_MAX]