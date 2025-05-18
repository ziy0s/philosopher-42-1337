/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:35:20 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/16 09:12:14 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	get_forks(t_philo *philo)
{
	int	id;

	id = philo->id - 1;
	sem_wait(philo->data->sem_forks[id]);
	print_message(philo, "has taken a fork");
	sem_wait(philo->data->sem_forks[(id + 1) % philo->data->num_philos]);
	print_message(philo, "has taken a fork");
}

static void	release_forks(t_philo *philo)
{
	int	id;

	id = philo->id - 1;
	sem_post(philo->data->sem_forks[id]);
	sem_post(philo->data->sem_forks[(id + 1) % philo->data->num_philos]);
}

static void	simulation(t_philo *philo)
{
	pthread_t	mutex;

	philo->eat_time = get_time();
	if (pthread_create(&mutex, NULL, (void *)monitored, philo) != 0)
		return (wait_philosophers(philo->data), ft_exit(1));
	if (pthread_detach(mutex) != 0)
		return (wait_philosophers(philo->data), ft_exit(1));
	while (1)
	{
		get_forks(philo);
		philo->eat_time = get_time();
		print_message(philo, "is eating");
		philo->num_eats++;
		philo->flag = 1;
		ft_usleep(philo->data->time_to_eat);
		release_forks(philo);
		philo->flag = 0;
		if (philo->num_eats == philo->data->num_meals)
			break ;
		print_message(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_message(philo, "is thinking");
	}
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	stop_thread;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i]->pid = fork();
		if (data->philos[i]->pid < 0)
		{
			wait_philosophers(data);
			write(2, "fork faild ", 12);
			ft_exit(1);
		}
		else if (data->philos[i]->pid == 0)
		{
			simulation(data->philos[i]);
			ft_exit(0);
		}
		i++;
	}
	if (pthread_create(&stop_thread, NULL, monitor_stop, data) < 0)
		return (wait_philosophers(data), ft_exit(1));
	if (pthread_detach(stop_thread) < 0)
		return (wait_philosophers(data), ft_exit(1));
}
