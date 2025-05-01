/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:36:54 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/01 14:50:26 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] || s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

void	exc_job(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->eat_mutex);
	ptr->eat_time = get_time();
	pthread_mutex_unlock(&ptr->eat_mutex);
	print_msg(ptr->data, ptr, "is eating");
	ft_usleep(ptr->data->time_eat);
	pthread_mutex_unlock(ptr->l_fork);
	pthread_mutex_unlock(ptr->r_fork);
	ptr->num_eat++;
	print_msg(ptr->data, ptr, "is sleeping");
	ft_usleep(ptr->data->time_sleep);
	print_msg(ptr->data, ptr, "is thinking");
}

int	get_args(char *v[], t_data **ptr)
{
	(*ptr)->num_philo = ft_atoi(v[1]);
	if ((*ptr)->num_philo < 1 || (*ptr)->num_philo > 200)
		return (ft_exit(1, NULL));
	(*ptr)->time_die = ft_atoi(v[2]);
	(*ptr)->time_eat = ft_atoi(v[3]);
	if ((*ptr)->time_eat < 60 || (*ptr)->time_die < 60)
		return (ft_exit(1, NULL));
	(*ptr)->time_sleep = ft_atoi(v[4]);
	if ((*ptr)->time_sleep < 60)
		return (ft_exit(1, NULL));
	return (0);
}
