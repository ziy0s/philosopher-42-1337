/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:00:09 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/16 09:11:42 by zaissi           ###   ########.fr       */
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
# include <signal.h>

typedef struct s_philo
{
	int				id;
	int				pid;
	int				flag;
	int				num_eats;
	int64_t			eat_time;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int			num_philos;
	int			num_meals;
	char		**forks;
	char		*print;
	char		*stop;
	int64_t		time_to_die;
	int64_t		time_to_eat;
	int64_t		time_to_sleep;
	int64_t		start_time;
	sem_t		**sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_stop;
	t_philo		**philos;
}				t_data;

char	*ft_itoa(pid_t nbr);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		ft_intsize(int nbr);
int		ft_strcmp(const char *s1, const char *s2);
int64_t	get_time(void);
t_data	*init_data(char *v[]);
void	*ft_malloc(size_t size);
void	print_message(t_philo *philo, char *message);
void	ft_usleep(int64_t time);
void	ft_exit(int status);
void	cleanup(t_data *data, int s);
void	monitored(t_philo *philo);
void	start_simulation(t_data *data);
void	*monitor_stop(void *arg);
void	wait_philosophers(t_data *data);

#endif