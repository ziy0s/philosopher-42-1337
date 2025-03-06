/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:39:03 by zaissi            #+#    #+#             */
/*   Updated: 2025/03/06 05:32:35 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <libc.h>

void	error(int status)
{
	if (status)
		write(2, "Error\n", 7);
	ft_exit(status);
}

uint64_t	get_time(t_data *ptr)
{
	struct timeval now;
	u_int64_t	time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time - ptr->start);
}

// void *monitor(void *arg) {
//     t_data *data = (t_data *)arg;
//     while (1) {
//         usleep(1000);
//         for (int i = 0; i < data->num_philo; i++) {
//             pthread_mutex_lock(&data->philo[i].eat_mutex);
//             uint64_t time_since_meal = get_time(data) - data->philo[i].eat_time;
//             if (time_since_meal > data->time_die) {
//                 printf("%llu\t%d died\n", get_time(data), data->philo[i].id);
//                 pthread_mutex_unlock(&data->philo[i].eat_mutex);
//                 return (NULL);
//             }
//             pthread_mutex_unlock(&data->philo[i].eat_mutex);
//         }
//     }
//     return (NULL);
// }

void	args(char *v[], t_data **ptr)
{
	(*ptr) = ft_malloc(sizeof(t_data));
	(*ptr)->num_philo = ft_atoi(v[1]);
	if ((*ptr)->num_philo < 1 || (*ptr)->num_philo > 200)
		ft_exit(1);
	(*ptr)->time_die = ft_atoi(v[2]);
	if ((*ptr)->time_die < 60)
		ft_exit(1);
	(*ptr)->time_eat = ft_atoi(v[3]);
	if ((*ptr)->time_eat < 60)
		ft_exit(1);
	(*ptr)->time_sleep = ft_atoi(v[4]);
	if ((*ptr)->time_sleep < 60)
		ft_exit(1);
	(*ptr)->philo = ft_malloc(sizeof(t_philo) * (*ptr)->num_philo);
	(*ptr)->forks = ft_malloc((*ptr)->num_philo * sizeof(pthread_mutex_t));
	(*ptr)->start = 0;
	(*ptr)->start = get_time(*ptr);
	if (v[5])
	{
		(*ptr)->num_eat = ft_atoi(v[5]);
		if ((*ptr)->num_eat < 1)
			ft_exit(2);
	}
	else
		(*ptr)->num_eat = -1;
}

void init_philo(t_data	**ptr)
{
	t_data *tmp;
	int		i;

	tmp = *ptr;
	i = 0;
	tmp->forks = malloc(sizeof(pthread_mutex_t) * tmp->num_philo);
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
		tmp->philo[i].eat_time = 0;
		i++;
	}
}

void	go_to_sleep(t_philo *ptr)
{
	printf("%llu\t%d is sleeping\n", get_time(ptr->data), ptr->id);
	usleep(ptr->data->time_sleep * 1000);
}

void	git_fork(t_philo *ptr)
{
	if (ptr->id % 2 == 0)
	{
		pthread_mutex_lock(ptr->l_fork);
		pthread_mutex_lock(ptr->r_fork);
		printf("%llu\t%d has taken a fork\n", get_time(ptr->data), ptr->id);
	}
	else
	{
		pthread_mutex_lock(ptr->r_fork);
		pthread_mutex_lock(ptr->l_fork);
		printf("%llu\t%d has taken a fork\n", get_time(ptr->data), ptr->id);
	}
}

void *eating(void *arg)
{
    t_philo *ptr;

	ptr = (t_philo *)arg;
    while (1)
	{
		git_fork(ptr);
		
		// pthread_mutex_lock(&ptr->eat_mutex);
		// ptr->eat_time = get_time(ptr->data);

        printf("%llu\t%d is eating\n", get_time(ptr->data), ptr->id);
        usleep(ptr->data->time_eat * 1000);
		ptr->eat_time = 0;
        pthread_mutex_unlock(ptr->l_fork);
        pthread_mutex_unlock(ptr->r_fork);
        ptr->num_eat++;
        if (ptr->num_eat == ptr->data->num_eat)
            break;
		go_to_sleep(ptr);
		printf("%llu\t%d is thinking\n", get_time(ptr->data), ptr->id);
		ptr->eat_time += ptr->data->time_sleep * 1000;
	}
    return (NULL);
}

void	creat_threads(t_data **tmp)
{
	t_data	*ptr;
	pthread_t	*thread;
	int 	i;

	ptr = *tmp;
	thread = ft_malloc(sizeof(pthread_t) * ptr->num_philo);
	i = 0;
	while (i < ptr->num_philo)
	{
		ptr->philo[i].thread = thread[i];
		pthread_create(&thread[i], NULL, &eating, &ptr->philo[i]);
		i++;
	}
	i = 0;
	while (i < ptr->num_philo)
	{
		if (ptr->philo[i].eat_time >= (uint64_t) ptr->time_die)
		{
			printf("%llu\t%d died\n", get_time(ptr), ptr->philo[i].id);
			error(0);
		}
		else
			pthread_join(thread[i], NULL);
		i++;
	}
}

int	main(int c, char *v[])
{
	t_data	*ptr;

	ptr = NULL;
	if (c < 5 || c > 6)
	{
		write(2, "Error\nInvalid Args!\n", 21);
		exit(1);
	}
	else
		args(v, &ptr);
	init_philo(&ptr);
	creat_threads(&ptr);
}
