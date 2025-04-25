/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:34:11 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/25 07:15:39 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void    print_message(t_philo *philo, char *message)
{
    sem_wait(philo->data->sem_print);
    printf("%ld\t%d %s\n", get_time() - philo->data->start_time, philo->id, message);
    sem_post(philo->data->sem_print);
}