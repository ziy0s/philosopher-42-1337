/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:26:22 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/18 09:16:05 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*eating(void *arg)
{
	t_philo	*ptr;

	ptr = (t_philo *)arg;
	if (ptr->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (ptr->data->num_philo == 1)
		{
			pthread_mutex_lock(ptr->l_fork);
			print_msg(ptr->data, ptr, "has taken a fork");
			ft_usleep(ptr->data->time_die + 1);
			pthread_mutex_unlock(ptr->l_fork);
			return (NULL);
		}
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

static void	*monitoring(void *arg)
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
			if ((get_time() - ptr->philo[i].eat_time > ptr->time_die)
				&& !ptr->philo[i].flag)
				return (if_dead(ptr, i), NULL);
			if (ptr->num_eat != -1)
			{
				if (ptr->philo[i].num_eat < ptr->num_eat)
					all = 0;
			}
			pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
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
	if (!thread)
		return (1);
	i = -1;
	while (++i < ptr->num_philo)
		if (pthread_create(&thread[i], NULL, &eating, &ptr->philo[i]) != 0)
			return (free_threads(thread, i));
	if (pthread_create(&monitor, NULL, &monitoring, ptr) != 0)
		return (free_threads(thread, i));
	pthread_join(monitor, NULL);
	i = 0;
	while (i < ptr->num_philo)
	{
		pthread_detach(thread[i]);
		i++;
	}
	while (!ptr->stop)
		;
	return (0);
}
