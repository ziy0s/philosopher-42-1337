/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 04:59:53 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/03 07:17:59 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitored(t_philo *philo)
{
	int64_t	time;

	while (1)
	{
		time = get_time() - philo->eat_time;
		if (time > philo->data->time_to_die)
		{
			sem_wait(philo->data->sem_print);
			printf("%lld\t%d died\n", get_time() - philo->data->start_time,
				philo->id);
			sem_post(philo->data->sem_stop);
			ft_exit(0);
		}
		else
			usleep(1000);
	}
}

void	*monitor_stop(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	sem_wait(data->sem_stop);
	i = 0;
	while (i < data->num_philos)
	{
		kill(data->philos[i]->pid, SIGKILL);
		i++;
	}
	return (NULL);
}

void	wait_philosophers(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < data->num_philos)
			{
				kill(data->philos[i]->pid, SIGKILL);
				i++;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong arguments\n");
		return (1);
	}
	data = init_data(argv);
	start_simulation(data);
	wait_philosophers(data);
	cleanup(data, 0);
}
