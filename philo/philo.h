/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:39:53 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/12 21:17:22 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int							id;
	int							num_eat;
	pthread_mutex_t				*l_fork;
	pthread_mutex_t				*r_fork;
	struct s_data				*data;
	uint64_t					eat_time;
	pthread_mutex_t				eat_mutex;
	uint64_t					old;
}				t_philo;

typedef struct s_data
{
	int					num_philo;
	uint64_t			time_die;
	int					time_eat;
	int					time_sleep;
	int					num_eat; // -1
	int					is_die;
	t_philo				*philo;
	uint64_t			start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_m;
	pthread_mutex_t		protect;
	pthread_mutex_t		stop_protect;
}				t_data;

int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		*ft_malloc(size_t size);
int			print_msg(t_data *ptr, t_philo *phil, char *str);
int			creat_threads(t_data **tmp);
void		git_fork(t_philo *ptr);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_usleep(useconds_t time);
void		exc_job(t_philo *ptr);
int			ft_exit(int i, t_data *ptr);
int			get_args(char *v[], t_data **ptr);

#endif