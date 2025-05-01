/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:26:22 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/01 15:06:25 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating(void *arg)
{
	t_philo	*ptr;

	ptr = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&ptr->data->protect);
		if (ptr->data->stop)
		{
			pthread_mutex_unlock(&ptr->data->protect);
			break ;
		}
		pthread_mutex_unlock(&ptr->data->protect);
		if (ptr->data->num_eat != -1 && ptr->num_eat >= ptr->data->num_eat)
			break ;
		git_fork(ptr);
		exc_job(ptr);
	}
	return (NULL);
}

static void	if_dead(t_data *ptr, int i)
{
	pthread_mutex_lock(&ptr->protect);
	ptr->stop = 1;
	pthread_mutex_unlock(&ptr->protect);
	print_msg(ptr, &ptr->philo[i], "died");
	pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
}

static int	all_eat(t_data *ptr, int all)
{
	if (ptr->num_eat != -1 && all)
	{
		pthread_mutex_lock(&ptr->protect);
		ptr->stop = 1;
		pthread_mutex_unlock(&ptr->protect);
		return (1);
	}
	else
		return (0);
}

void	*monitoring(void *arg)
{
	t_data	*ptr;
	int		i;
	int		all;

	ptr = (t_data *)arg;
	while (1)
	{
		(1) && (all = 1, i = -1);
		while (++i < ptr->num_philo)
		{
			pthread_mutex_lock(&ptr->philo[i].eat_mutex);
			if (get_time() - ptr->philo[i].eat_time > ptr->time_die)
				return (if_dead(ptr, i), NULL);
			pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
			if (ptr->num_eat != -1)
			{
				pthread_mutex_lock(&ptr->philo[i].eat_mutex);
				if (ptr->philo[i].num_eat < ptr->num_eat)
					all = 0;
				pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
			}
		}
		if (all_eat(ptr, all))
			return (NULL);
	}
}

int	creat_threads(t_data **tmp)
{
	t_data		*ptr;
	pthread_t	*thread;
	pthread_t	monitor;
	int			i;

	ptr = *tmp;
	thread = ft_malloc(sizeof(pthread_t) * ptr->num_philo);
	i = -1;
	while (++i < ptr->num_philo)
		if (pthread_create(&thread[i], NULL, &eating, &ptr->philo[i]) != 0)
			return (1);
	if (pthread_create(&monitor, NULL, &monitoring, ptr) != 0)
		return (1);
	pthread_join(monitor, NULL);
	if (ptr->stop)
		return (0);
	i = 0;
	while (i < ptr->num_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}
