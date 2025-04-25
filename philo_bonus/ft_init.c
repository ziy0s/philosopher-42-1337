/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 05:10:18 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/25 23:31:26 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

static t_philo  **init_philos(t_data *data)
{
    t_philo **philos;
    int     i;

    philos = ft_malloc(sizeof(t_philo *) * data->num_philos);
    i = 0;
    while (i < data->num_philos)
    {
        philos[i] = ft_malloc(sizeof(t_philo));
        philos[i]->id = i + 1;
        philos[i]->num_eats = 0;
        philos[i]->eat_time = data->start_time;
        philos[i]->data = data;
        i++;
    }
    return (philos);
}

char    *make_sem_name(const char *str)
{
    char    *name;
    char    *pid;
    int     size;
    int     i;
    int     j;

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
    pid = ft_itoa(getpid());
    return (ft_strjoin(name, pid));
}

t_data  *init_data(char *v[])
{
    t_data  *data;

    data = ft_malloc(sizeof(t_data));
    data->num_philos = ft_atoi(v[1]);
    data->time_to_die = ft_atoi(v[2]);
    data->time_to_eat = ft_atoi(v[3]);
    data->time_to_sleep = ft_atoi(v[4]);
    if (v[5])
        data->num_meals = ft_atoi(v[5]);
    else
        data->num_meals = -1;
    if (data->num_philos < 1 || data->num_philos > 250 || 
        data->time_to_die < 60 || data->time_to_eat < 60 ||
        data->time_to_sleep < 60)
    {
        write(2, "Error\n", 7);
        exit(1);
    }
    data->start_time = get_time();
    // sem_unlink("/sem_forks");
    // sem_unlink("/sem_print");
    // sem_unlink("/sem_meals");
    // sem_unlink("/sem_death");
    // sem_unlink("/sem_stop");
    data->sem_forks = sem_open(make_sem_name("forks"), O_CREAT | O_EXCL, 0644, data->num_philos);
    data->sem_print = sem_open(make_sem_name("print"), O_CREAT | O_EXCL, 0644, 1);
    data->sem_meals = sem_open(make_sem_name("meals"), O_CREAT | O_EXCL, 0644, data->num_philos);
    data->sem_death = sem_open(make_sem_name("death"), O_CREAT | O_EXCL, 0644, 1);
    data->sem_stop = sem_open(make_sem_name("stop"), O_CREAT | O_EXCL, 0644, 1);
    if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED ||
        data->sem_meals == SEM_FAILED || data->sem_death == SEM_FAILED ||
        data->sem_stop == SEM_FAILED)
    {
        perror("Error: Failed to create semaphores");
        exit(1);
    }
    data->philos = init_philos(data);
    data->start_time = get_time(); 

    return (data);
}
