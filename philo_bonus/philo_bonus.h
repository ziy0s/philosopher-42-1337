/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:49:55 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/13 19:29:24 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
#include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct  s_philo
{
	int     		id;
	int             num_eat;
	pid_t           pid;
	struct s_data   *data;
	sem_t			l_fork;
	sem_t			r_fork;
}               t_philo;

typedef struct  s_data
{
	int			num_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			num_eat;
	t_philo		*philo;
	uint64_t	time;
	uint64_t	time_start;
	int			start;
	sem_t		*write;
	sem_t		*forks;
}               t_data;

void	*ft_malloc(size_t size);
int	ft_atoi(const char *str);
int	ft_exit(int i);
int	print_msg(t_data *ptr, t_philo *phil, char *str);
int	ft_strcmp(const char *s1, const char *s2);
uint64_t	get_time(void);
int	ft_usleep(useconds_t time);

#endif