/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:14:27 by zaissi            #+#    #+#             */
/*   Updated: 2025/03/11 22:39:08 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int     checker(int *flag, t_data *ptr)
// {
// 	pthread_mutex_lock(&ptr->protect);
// 	*flag = ptr->stop;
// 	pthread_mutex_unlock(&ptr->protect);
// 	return (*flag);
// }

// void    print_msg(t_data *ptr, t_philo *phil, char *str, int *flag)
// {
// 	uint64_t	time;

// 	*flag = 0;
// 	time = get_time() - ptr->start;
// 	// if (checker(flag, ptr))
// 	// 	return ;
// 	pthread_mutex_lock(&ptr->write_m);
// 	printf("%llu\t%d %s\n", time, phil->id, str);
// 	// pthread_mutex_unlock(&ptr->write_m);
// 	if (ft_strcmp(str, "is die") == 0)
// 		return ;
// 	pthread_mutex_unlock(&ptr->write_m);
// }

void print_msg(t_data *ptr, t_philo *phil, char *str, int *flag)
{
    uint64_t time;

	*flag = 0;
    pthread_mutex_lock(&ptr->write_m);
    time = get_time() - ptr->start;
    printf("%llu\t%d %s\n", time, phil->id, str);
    pthread_mutex_unlock(&ptr->write_m); // Always unlock
}