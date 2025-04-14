/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:39:03 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/13 19:20:55 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	args(char *v[], t_data **ptr)
{
	(*ptr) = ft_malloc(sizeof(t_data));
	if (!(*ptr))
		return (1);
	if (get_args(v, ptr))
		return (1);
	(*ptr)->philo = ft_malloc(sizeof(t_philo) * (*ptr)->num_philo);
	if (!(*ptr)->philo)
		return (1);
	(*ptr)->forks = ft_malloc((*ptr)->num_philo * sizeof(pthread_mutex_t));
	if (!(*ptr)->forks)
		return (1);
	(*ptr)->start = get_time();
	(*ptr)->is_die = 0;
	if (v[5])
	{
		(*ptr)->num_eat = ft_atoi(v[5]);
		if ((*ptr)->num_eat < 1)
			return (ft_exit(1, NULL));
	}
	else
		(*ptr)->num_eat = -1;
	return (0);
}

void	init_philo(t_data	**ptr)
{
	t_data	*tmp;
	int		i;

	tmp = *ptr;
	i = 0;
	tmp->forks = ft_malloc(sizeof(pthread_mutex_t) * tmp->num_philo);
	while (i < tmp->num_philo)
	{
		pthread_mutex_init(&tmp->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < tmp->num_philo)
	{
		tmp->philo[i].id = i + 1;
		tmp->philo[i].l_fork = &tmp->forks[i];
		tmp->philo[i].r_fork = &tmp->forks[(i + 1) % tmp->num_philo];
		tmp->philo[i].data = tmp;
		tmp->philo[i].num_eat = 0;
		tmp->philo[i].old = -1;
		pthread_mutex_init(&tmp->philo[i].eat_mutex, NULL);
		tmp->philo[i].eat_time = get_time();
		i++;
	}
}

void	git_fork(t_philo *ptr)
{
	if (ptr->id % 2 == 0)
	{
		print_msg(ptr->data, ptr, "has taken a fork");
		pthread_mutex_lock(ptr->l_fork);
		pthread_mutex_lock(ptr->r_fork);
		print_msg(ptr->data, ptr, "has taken a fork");
	}
	else
	{
		print_msg(ptr->data, ptr, "has taken a fork");
		pthread_mutex_lock(ptr->r_fork);
		pthread_mutex_lock(ptr->l_fork);
		print_msg(ptr->data, ptr, "has taken a fork");
	}
}

int	main(int c, char *v[])
{
	t_data	*ptr;

	ptr = NULL;
	if (c < 5 || c > 6)
	{
		write(2, "Error\nInvalid Args!\n", 21);
		return (1);
	}
	else
		if (args(v, &ptr))
			return (1);
	pthread_mutex_init(&ptr->write_m, NULL);
	pthread_mutex_init(&ptr->protect, NULL);
	pthread_mutex_init(&ptr->stop_protect, NULL);
	init_philo(&ptr);
	if (creat_threads(&ptr) == 1)
		return (ft_exit(1, ptr));
	return (0);
}
