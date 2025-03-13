/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:39:03 by zaissi            #+#    #+#             */
/*   Updated: 2025/03/11 22:38:03 by zaissi           ###   ########.fr       */
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

uint64_t	get_time()
{
	struct timeval now;
	uint64_t	time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time);
}

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
	(*ptr)->start = get_time();
	(*ptr)->is_die = 0;
	if (v[5])
	{
		(*ptr)->num_eat = ft_atoi(v[5]);
		if ((*ptr)->num_eat < 1)
			ft_exit(2);
	}
	else
		(*ptr)->num_eat = -1;
}

// void init_philo(t_data	**ptr)
// {
// 	t_data *tmp;
// 	int		i;

// 	tmp = *ptr;
// 	i = 0;
// 	tmp->forks = malloc(sizeof(pthread_mutex_t) * tmp->num_philo);
// 	while (i < tmp->num_philo)
// 	{
// 		pthread_mutex_init(&tmp->forks[i], NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < tmp->num_philo)
// 	{
// 		tmp->philo[i].id = i + 1;
// 		tmp->philo[i].l_fork = &tmp->forks[i];
// 		tmp->philo[i].r_fork = &tmp->forks[(i + 1) % tmp->num_philo];
// 		tmp->philo[i].data = tmp;
// 		tmp->philo[i].num_eat = 0;
// 		tmp->philo[i].old = -1;
// 		// tmp->philo[i].eat_time = 0;
// 		pthread_mutex_init(&tmp->philo[i].eat_mutex, NULL);
// 		tmp->philo[i].eat_time = get_time();
// 		i++;
// 	}
// }

void init_philo(t_data **ptr)
{
    t_data *tmp = *ptr;
    int i = 0;

    // Initialize forks (already allocated in args())
    while (i < tmp->num_philo)
    {
        pthread_mutex_init(&tmp->forks[i], NULL);
        i++;
    }

    // Initialize philosophers
    i = 0;
    while (i < tmp->num_philo)
    {
        tmp->philo[i].id = i + 1;
        tmp->philo[i].l_fork = &tmp->forks[i];
        tmp->philo[i].r_fork = &tmp->forks[(i + 1) % tmp->num_philo];
        tmp->philo[i].data = tmp;
        tmp->philo[i].num_eat = 0;
        pthread_mutex_init(&tmp->philo[i].eat_mutex, NULL);
        tmp->philo[i].eat_time = get_time(); // Initialize to simulation start
        i++;
    }
}

// void	go_to_sleep(t_philo *ptr, int *flag)
// {
// 	print_msg(ptr->data, ptr, "is sleeping", flag);
// 	ft_usleep(ptr->data->time_sleep);
// }

void	git_fork(t_philo *ptr, int *flag)
{
	if (ptr->id % 2 == 0)
	{
		pthread_mutex_lock(ptr->l_fork);
		pthread_mutex_lock(ptr->r_fork);
		print_msg(ptr->data, ptr, "has taken a fork", flag);
	}
	else
	{
		pthread_mutex_lock(ptr->r_fork);
		pthread_mutex_lock(ptr->l_fork);
		print_msg(ptr->data, ptr, "has taken a fork", flag);
	}
}

// int	check_is_die(t_philo **ptr)
// {
// 	int64_t	diff;
// 	int			flag;

// 	pthread_mutex_lock(&(*ptr)->eat_mutex);
// 	if ((int64_t) (get_time() - (*ptr)->eat_time) < 0)
// 		diff = - get_time() - ((*ptr)->eat_time);
// 	else
// 		diff = (int64_t) (get_time() - (*ptr)->eat_time);
// 	flag = 0;
// 	printf("%llu\t:\t%llu\n", diff, (int64_t) (*ptr)->data->time_die);
// 	if (diff >= (int64_t) (*ptr)->data->time_die || (*ptr)->data->num_philo == 1)
// 	{
// 		pthread_mutex_lock(&(*ptr)->data->stop_protect);
// 		(*ptr)->data->is_die = 1;
// 		print_msg((*ptr)->data, *ptr, "is die", &flag);
// 			return (1);
// 		pthread_mutex_unlock(&(*ptr)->data->stop_protect);
// 	}
// 	pthread_mutex_unlock(&(*ptr)->eat_mutex);
// 	return (0);
// }

// void *eating(void *arg)
// {
//     t_philo *ptr;
// 	int		flag;

// 	ptr = (t_philo *)arg;
// 	flag = 0;
// 	printf("%d\n", ptr->data->is_die);
//     while (ptr->num_eat != ptr->data->num_eat && !ptr->data->is_die)
// 	{
// 		// if (check_is_die(&ptr) == 1)
// 		// {
// 		// 	ptr->data->is_die = 1;
// 		// 	return (NULL);
// 		// }
// 		git_fork(ptr, &flag);

// 		print_msg(ptr->data, ptr, "is eating", &flag);

// 		// printf("%d\n", ptr->data->time_eat);
//         ft_usleep(ptr->data->time_eat);

		
//         pthread_mutex_unlock(ptr->l_fork);
//         pthread_mutex_unlock(ptr->r_fork);
//         ptr->num_eat++;
		

// 		ptr->eat_time = get_time();

// 		// pthread_mutex_lock(&ptr->eat_mutex);
// 		// ptr->old = get_time();
// 		// pthread_mutex_unlock(&ptr->eat_mutex);

// 		// go_to_sleep(ptr, &flag);
// 		print_msg(ptr->data, ptr, "is sleeping", &flag);
// 		ft_usleep(ptr->data->time_sleep);
// 		print_msg(ptr->data, ptr, "is thinking", &flag);
// 		ft_usleep(ptr->data->time_sleep);
// 	}
//     return (NULL);
// }

void *eating(void *arg)
{
    t_philo *ptr = (t_philo *)arg;
    int flag = 0;

    while (ptr->num_eat != ptr->data->num_eat && !ptr->data->is_die)
    {
        git_fork(ptr, &flag); // Acquire forks

        // Update eat_time when eating starts
        pthread_mutex_lock(&ptr->eat_mutex);
        ptr->eat_time = get_time();
        pthread_mutex_unlock(&ptr->eat_mutex);

        print_msg(ptr->data, ptr, "is eating", &flag);
        ft_usleep(ptr->data->time_eat);

        pthread_mutex_unlock(ptr->l_fork);
        pthread_mutex_unlock(ptr->r_fork);
        ptr->num_eat++;

        print_msg(ptr->data, ptr, "is sleeping", &flag);
        ft_usleep(ptr->data->time_sleep);
        print_msg(ptr->data, ptr, "is thinking", &flag);
    }
    return (NULL);
}

// void	*monitoring(void *arg)
// {
// 	t_data *ptr;
// 	int		i;

// 	ptr = (t_data *) arg;
// 	i = 0;
// 	while (i < ptr->num_philo)
// 	{
// 		// if (check_is_die(&ptr->philo[i]) == 1)
// 		// {
// 		// 	ptr->is_die = 1;
// 		// 	return (NULL);
// 		// }

// 		int64_t	diff;
// 		int			flag;
// 		pthread_mutex_lock(&ptr->philo[i].eat_mutex);
// 		printf("kfdsjflsd\n");
// 		if ((int64_t) (get_time() - ptr->philo[i].eat_time) < 0)
// 			diff = - get_time() - (ptr->philo[i].eat_time);
// 		else
// 			diff = (int64_t) (get_time() - ptr->philo[i].eat_time);
// 		flag = 0;
// 		printf("kljkldsfjdklsfjdklsfjdksfj\n");
// 		printf("%llu\t:\t%llu\n", diff, (int64_t) ptr->time_die);
// 		if (diff >= (int64_t) ptr->time_die || ptr->num_philo == 1)
// 		{
// 			pthread_mutex_lock(&ptr->stop_protect);
// 			ptr->is_die = 1;
// 			print_msg(ptr, &ptr->philo[i], "is die", &flag);
// 				return (NULL);
// 			pthread_mutex_unlock(&ptr->stop_protect);
// 		}
// 		pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
// 	// return (0);
// 		i++;
// 	}
// 	return (NULL);
// }

void *monitoring(void *arg)
{
    t_data *ptr = (t_data *)arg;
    uint64_t current_time, diff;

    while (1)
    {
        int i = 0;
        while (i < ptr->num_philo)
        {
            pthread_mutex_lock(&ptr->philo[i].eat_mutex);
            current_time = get_time();
            diff = current_time - ptr->philo[i].eat_time;
			// printf("kldsjfkljsdfkldjs\n");
            if (diff >= ptr->time_die)
            {
                pthread_mutex_lock(&ptr->stop_protect);
                ptr->is_die = 1;
                pthread_mutex_unlock(&ptr->stop_protect); // 🔑 Unlock before printing
                print_msg(ptr, &ptr->philo[i], "died", &ptr->is_die);
                pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&ptr->philo[i].eat_mutex);
            i++;
        }
        usleep(1000); // Reduce CPU usage
    }
    return (NULL);
}

// int	creat_threads(t_data **tmp)
// {
// 	t_data	*ptr;
// 	pthread_t	*thread;
// 	int 	i;
// 	pthread_t	monitor;

// 	ptr = *tmp;
// 	thread = ft_malloc(sizeof(pthread_t) * ptr->num_philo);
// 	i = 0;
// 	while (i < ptr->num_philo)
// 	{
// 		ptr->philo[i].thread = thread[i];
// 		pthread_create(&thread[i], NULL, &eating, &ptr->philo[i]);
// 		pthread_create(&monitor, NULL, &monitoring, &ptr);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < ptr->num_philo)
// 	{
// 		pthread_join(thread[i], NULL);
// 		pthread_join(monitor, NULL);
// 		if (ptr->is_die)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int creat_threads(t_data **tmp)
{
    t_data *ptr = *tmp;
    pthread_t *thread;
    pthread_t monitor; // Single monitor thread
    int i;

    thread = ft_malloc(sizeof(pthread_mutex_t) * ptr->num_philo);

    // Create philosopher threads
    i = 0;
    while (i < ptr->num_philo)
    {
        pthread_create(&thread[i], NULL, &eating, &ptr->philo[i]);
        i++;
    }

    // Create one monitor thread
    pthread_create(&monitor, NULL, &monitoring, ptr);

    // Wait for all philosopher threads
    i = 0;
    while (i < ptr->num_philo)
    {
        pthread_join(thread[i], NULL);
        i++;
    }

    // Wait for the monitor thread
    pthread_join(monitor, NULL);

    return (0);
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
	pthread_mutex_init(&ptr->write_m, NULL);
	pthread_mutex_init(&ptr->protect, NULL);
	pthread_mutex_init(&ptr->stop_protect, NULL);
	init_philo(&ptr);
	if (creat_threads(&ptr) == 1)
		printf("klsjdfkljsdfkljds\n");
	return (0);
}
