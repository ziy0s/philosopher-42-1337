/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:10:18 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/30 16:47:54 by zaissi           ###   ########.fr       */
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

char	*make_sem_name(const char *str)
{
	char	*name;
	char	*ret;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = ft_intsize(getpid());
	name = ft_malloc(sizeof(char) * (ft_strlen(str) + size + 2));
	name[0] = '/';
	j = 1;
	while (str[i])
	{
		name[j] = str[i];
		j++;
		i++;
	}
	name[j] = '_';
	j++;
	ret = ft_strjoin(name, ft_itoa(getpid()));
	return (ret);
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

t_data	*init_data(char *v[])
{
	t_data	*data;
	int		i;
	int		flag;

	data = ft_malloc(sizeof(t_data));
	data = init_args(v, data);
	data->sem_forks = (sem_t **)ft_malloc(sizeof(sem_t *) * data->num_philos);
	data->forks = ft_malloc(sizeof(char *) * data->num_philos);
	(1) && (i = 0, flag = O_CREAT | O_EXCL);
	data->print = make_sem_name("print");
	data->stop = make_sem_name("stop");
	while (i < data->num_philos)
	{
		data->forks[i] = make_sem_name(ft_itoa(i));
		data->sem_forks[i] = sem_open(data->forks[i], flag, 0644, 1);
		sem_unlink(data->forks[i]);
		i++;
	}
	data->sem_print = sem_open(data->print, flag, 0644, 1);
	data->sem_stop = sem_open(data->stop, flag, 0644, 0);
	if (data->sem_print == SEM_FAILED || data->sem_stop == SEM_FAILED)
		ft_exit(1);
	data->philos = init_philos(data);
	data->start_time = get_time();
	return (data);
}
