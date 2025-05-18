/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:14:27 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/18 09:28:37 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(t_data *ptr, t_philo *phil, char *str)
{
	uint64_t	time;

	pthread_mutex_lock(&ptr->write_m);
	if (!ft_strcmp("died", str))
		time = (get_time() - ptr->start) - 1;
	else
		time = get_time() - ptr->start;
	printf("%llu\t%d %s\n", time, phil->id, str);
	if (!ft_strcmp("died", str))
		return (0);
	pthread_mutex_unlock(&ptr->write_m);
	return (1);
}

int	free_threads(pthread_t *threads, int nuber_of_threads)
{
	int	i;

	i = 0;
	while (i < nuber_of_threads)
	{
		pthread_detach(threads[i]);
		i++;
	}
	return (1);
}
