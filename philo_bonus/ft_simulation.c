/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:35:20 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/25 23:22:37 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void    get_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        sem_wait(philo->data->sem_forks);
        print_message(philo, "has taken a fork");
        sem_wait(philo->data->sem_forks);
        print_message(philo, "has taken a fork");
    }
    else
    {
        sem_wait(philo->data->sem_forks);
        print_message(philo, "has taken a fork");
        sem_wait(philo->data->sem_forks);
        print_message(philo, "has taken a fork");
    }
}
