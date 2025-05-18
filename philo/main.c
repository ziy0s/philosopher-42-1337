/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:39:03 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/16 14:17:21 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

static int	args(char *v[], t_data **ptr)
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
	(*ptr)->stop = 0;
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

static int	init_philo(t_data	**ptr)
{
	t_data	*tmp;
	int		i;

	(1) && (i = 0, tmp = *ptr);
	tmp->forks = ft_malloc(sizeof(pthread_mutex_t) * tmp->num_philo);
	if (!tmp->forks)
		return (1);
	while (i < tmp->num_philo)
	{
		if (pthread_mutex_init(&tmp->forks[i], NULL) != 0)
			return (ft_exit(1, NULL));
		tmp->philo[i].id = i + 1;
		tmp->philo[i].flag = 0;
		tmp->philo[i].l_fork = &tmp->forks[i];
		tmp->philo[i].r_fork = &tmp->forks[(i + 1) % tmp->num_philo];
		tmp->philo[i].data = tmp;
		tmp->philo[i].num_eat = 0;
		if (pthread_mutex_init(&tmp->philo[i].eat_mutex, NULL) != 0)
			return (ft_exit(1, NULL));
		tmp->philo[i].eat_time = get_time();
		i++;
	}
	return (0);
}

void	git_fork(t_philo *ptr)
{
	pthread_mutex_lock(ptr->l_fork);
	print_msg(ptr->data, ptr, "has taken a fork");
	pthread_mutex_lock(ptr->r_fork);
	print_msg(ptr->data, ptr, "has taken a fork");
}

void f()
{
	system("leaks philo");
}
int	main(int c, char *v[])
{
	t_data	*ptr;
	// atexit(f);
	ptr = NULL;
	if (c < 5 || c > 6)
	{
		write(2, "Error\nInvalid Args!\n", 21);
		return (1);
	}
	else
		if (args(v, &ptr))
			return (1);
	if (pthread_mutex_init(&ptr->write_m, NULL) < 0)
		return (ft_exit(1, NULL));
	if (pthread_mutex_init(&ptr->protect, NULL) < 0)
		return (ft_exit(1, NULL));
	if (init_philo(&ptr))
		return (1);
	if (creat_threads(&ptr) == 1)
		return (ft_exit(1, ptr));
	return (ft_exit(0, ptr));
}
