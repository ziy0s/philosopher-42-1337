/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:57:37 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/13 19:29:16 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		ft_exit(1);
	(*ptr)->num_philo = ft_atoi(v[1]);
	if ((*ptr)->num_philo <= 0 || (*ptr)->num_philo > 200)
		return (1);
	(*ptr)->time_die = ft_atoi(v[2]);
	(*ptr)->time_eat = ft_atoi(v[3]);
	if ((*ptr)->time_eat < 60 || (*ptr)->time_die < 60)
		return (ft_exit(1));
	(*ptr)->time_sleep = ft_atoi(v[4]);
	if ((*ptr)->time_sleep < 60)
		return (ft_exit(1));
	(*ptr)->philo = ft_malloc(sizeof(t_philo) * (*ptr)->num_philo);
	if (!(*ptr)->philo)
		ft_exit(1);
	(*ptr)->time = 0;
	(*ptr)->time_start = get_time();
	(*ptr)->start = 0;
	if (v[5])
	{
		(*ptr)->num_eat = ft_atoi(v[5]);
		if ((*ptr)->num_eat <= 0)
			ft_exit(1);
	}
	else
		(*ptr)->num_eat = -1;
	return (0);
}

void	philo_int(t_data **ptr, int i)
{
	// (*ptr)->philo[i] = *(t_philo *)ft_malloc(sizeof(t_philo));
	(*ptr)->philo->pid = getpid();
	(*ptr)->philo->id = i;
	(*ptr)->philo->num_eat = 0;
	(*ptr)->forks = sem_open("/forks", O_CREAT, 0466, (*ptr)->num_philo);
	(*ptr)->write = sem_open("/write", O_CREAT, 0466, 1);
	// (*ptr)->philo[i].pid = -1;
}

void	get_forks(t_philo *ptr)
{
	if (ptr->id % 2 == 0)
	{
		print_msg(ptr->data, ptr, "has take a fork");
		sem_wait(&ptr->l_fork);
		sem_wait(&ptr->r_fork);
		print_msg(ptr->data, ptr, "has take a fork");
	}
	else
	{
		print_msg(ptr->data, ptr, "has take a fork");
		sem_wait(&ptr->r_fork);
		sem_wait(&ptr->l_fork);
		print_msg(ptr->data, ptr, "has take a fork");
	}
}

void	eating_proc(t_philo *philo)
{
	// printf("%d\n", ptr->id);
	// get_forks(ptr);
	int i = 0;
	while (i < 20) {
        // Take forks
        sem_wait(philo->data->forks);  // Take first fork
        print_msg(philo->data, philo, "has taken a fork");
        sem_wait(philo->data->forks);  // Take second fork
        print_msg(philo->data, philo, "has taken a fork");
        
        // Eat
        print_msg(philo->data, philo, "is eating");
        philo->data->time = get_time();
        ft_usleep(philo->data->time_eat);
        
        // Release forks
        sem_post(philo->data->forks);
        sem_post(philo->data->forks);
        
        // Sleep and think
        print_msg(philo->data, philo, "is sleeping");
        ft_usleep(philo->data->time_sleep);
        print_msg(philo->data, philo, "is thinking");
		i++;
    }
	kill(philo->pid, 3);
}

void	creat_philo(t_data **ptr)
{
	int i;
	int	id;
	
	id = fork();
	if (id == 0)
	{
		i = 1;
		while (i <= (*ptr)->num_philo && id == 0)
		{
			philo_int(ptr, i);
			// if (i + 1 > (*ptr)->num_philo)
			// 	break;
			id = fork();
			i++;
		}
		i = 1;
		while (i < (*ptr)->num_philo)
		{
			waitpid((*ptr)->philo->pid, NULL, 0);
			i++;
		}
		(*ptr)->start = 1;
		eating_proc((*ptr)->philo);
		// printf("%d\n", i);
	}
	// monitor_proc(ptr);
}

int main(int c, char *v[])
{
	t_data	*ptr;

	if (c < 5 || c > 6)
	{
		write(2, "Error\nInvalid Args!\n", 21);
		return (1);
	}
	else
		if (args(v, &ptr))
			return (ft_exit(1), 1);
	ptr->philo->data = ptr;
	// philo_int(&ptr);
	creat_philo(&ptr);
	// waitpid()
	// printf("%d\n", ptr->start);
}