/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 04:59:53 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/25 23:48:06 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	simulation(t_philo *philo)
{
	while (1)
	{
		get_forks(philo);
		print_message(philo, "is eating");
		philo->eat_time = get_time();
		philo->num_eats++;
		ft_usleep(philo->data->time_to_eat);
		philo->last_meal = get_time();
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		if (philo->num_eats == philo->data->num_meals)
		{
			sem_post(philo->data->sem_meals);
			break ;
		}
		print_message(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_message(philo, "is thinking");
	}
}

// void	monitored(t_philo *philo)
// {
// 	int		i;
// 	t_data	*data;

// 	data = philo->data;
// 	while (1)
// 	{
// 		i = -1;
// 		while (++i < data->num_philos)
// 		{
// 			if (get_time() - philo[i].eat_time > data->time_to_die)
// 			{
// 				print_message(&philo[i], "died");
// 				sem_wait(data->sem_print);
// 				sem_post(data->sem_death);
// 				ft_exit(0);
// 			}
// 		}
// 		usleep(1000);
// 	}
// }

void *monitored(void *arg)
{
    t_data  *data = (t_data *)arg;
    int     i;

    while (1)
    {
        i = -1;
        while (++i < data->num_philos)
        {
			printf("philo %d eat_time = %ld\n", data->philos[i]->id, data->philos[i]->eat_time);
            if (get_time() - data->philos[i]->eat_time > data->time_to_die)
            {
                print_message(data->philos[i], "died");
                sem_wait(data->sem_print);
                sem_post(data->sem_stop);
                ft_exit(0);
            }
        }
        usleep(1000);
    }
    return (NULL);
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	mutex;

	if (pthread_create(&mutex, NULL, monitored, data->philos) != 0)
	{
		perror("Error: Failed to create thread");
		ft_exit(1);
	}
	pthread_detach(mutex);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i]->pid = fork();
		if (data->philos[i]->pid < 0)
		{
			perror("Error: Fork failed");
			ft_exit(1);
		}
		else if (data->philos[i]->pid == 0)
		{
			simulation(data->philos[i]);
			ft_exit(0);
		}
		i++;
	}
}

int	main(int c, char *v[])
{
	t_data	*data;
	int		i;

	if (c < 5 || c > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	data = init_data(v);
	start_simulation(data);
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(data->philos[i]->pid, NULL, 0);
		i++;
	}
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_meals");
	sem_unlink("/sem_death");
	sem_unlink("/sem_stop");
	ft_exit(0);
}
