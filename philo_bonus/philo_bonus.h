/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:00:09 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/25 23:46:24 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				pid;
	int				num_eats;
	time_t			eat_time;
	struct s_data	*data;
	time_t			last_meal;
}				t_philo;

typedef struct s_data
{
	int			num_philos;
	int			num_meals;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	time_t		start_time;
	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_meals;
	sem_t		*sem_death;
	sem_t		*sem_stop;
	t_philo		**philos;
}				t_data;

t_data	*init_data(char *v[]);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		ft_intsize(int nbr);
void	*ft_malloc(size_t size);
void	print_message(t_philo *philo, char *message);
void	get_forks(t_philo *philo);
void	ft_usleep(time_t time);
void	ft_exit(int status);
char *ft_itoa(pid_t nbr);
char    *ft_strjoin(char const *s1, char const *s2);
// void *monitored(void *arg);

time_t	get_time(void);

#endif