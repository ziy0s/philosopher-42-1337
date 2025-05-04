/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:10:18 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/04 09:44:07 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = ft_malloc(sizeof(t_philo *) * data->num_philos);
	i = 0;
	while (i < data->num_philos)
	{
		philos[i] = ft_malloc(sizeof(t_philo));
		philos[i]->id = i + 1;
		philos[i]->num_eats = 0;
		philos[i]->eat_time = 0;
		philos[i]->data = data;
		i++;
	}
	return (philos);
}

static t_data	*init_args(char *v[], t_data *data)
{
	data->num_philos = ft_atoi(v[1]);
	data->time_to_die = ft_atoi(v[2]);
	data->time_to_eat = ft_atoi(v[3]);
	data->time_to_sleep = ft_atoi(v[4]);
	if (v[5])
		data->num_meals = ft_atoi(v[5]);
	else
		data->num_meals = -1;
	if (data->num_meals == 0)
		ft_exit(1);
	if (data->num_philos < 1 || data->num_philos > 250
		|| data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		ft_exit(1);
	data->start_time = get_time();
	return (data);
}

static t_data	*ft_sem_init(t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = O_CREAT | O_EXCL;
	data->print = ft_strdup("/print");
	data->stop = ft_strdup("/stop");
	sem_unlink(data->print);
	sem_unlink(data->stop);
	while (i < data->num_philos)
	{
		data->forks[i] = ft_strjoin("/fork", ft_itoa(i));
		sem_unlink(data->forks[i]);
		data->sem_forks[i] = sem_open(data->forks[i], flag, 0644, 1);
		if (data->sem_forks[i] == SEM_FAILED)
			cleanup(data, 1);
		i++;
	}
	data->sem_print = sem_open(data->print, flag, 0644, 1);
	data->sem_stop = sem_open(data->stop, flag, 0644, 0);
	if (data->sem_print == SEM_FAILED || data->sem_stop == SEM_FAILED)
		cleanup(data, 1);
	return (data);
}

t_data	*init_data(char *v[])
{
	t_data	*data;

	data = ft_malloc(sizeof(t_data));
	data = init_args(v, data);
	data->sem_forks = (sem_t **)ft_malloc(sizeof(sem_t *) * data->num_philos);
	data->forks = ft_malloc(sizeof(char *) * data->num_philos);
	data = ft_sem_init(data);
	if (data->sem_print == SEM_FAILED || data->sem_stop == SEM_FAILED)
		cleanup(data, 1);
	data->philos = init_philos(data);
	data->start_time = get_time();
	return (data);
}
