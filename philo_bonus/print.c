/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:26:28 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/13 19:30:51 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_msg(t_data *ptr, t_philo *phil, char *str)
{
	uint64_t	time;

	sem_wait(ptr->write);
	if (!ft_strcmp("died", str))
		time = (get_time() - ptr->time_start) - 1;
	else
		time = (get_time() - ptr->time_start);
	printf("%llu\t%d %s\n", time, phil->id, str);
	if (!ft_strcmp("died", str))
		exit (0);
	sem_post(ptr->write);
    return (0);
}