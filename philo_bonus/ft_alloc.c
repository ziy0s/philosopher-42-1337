/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:04:17 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/02 10:08:52 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_free(void *ptr, int flag)
{
	static void	*lst[INT_MAX];
	static int	i;
	int			j;

	if (flag)
	{
		j = 0;
		while (lst[j])
		{
			free (lst[j]);
			j++;
		}
	}
	else
		lst[i++] = ptr;
}

void	cleanup(t_data *data, int s)
{
	int	i;

	if (!data)
		ft_exit(1);
	sem_post(data->sem_stop);
	sem_close(data->sem_print);
	sem_unlink(data->print);
	sem_close(data->sem_stop);
	sem_unlink(data->stop);
	i = 0;
	while (i < data->num_philos)
	{
		sem_close(data->sem_forks[i]);
		sem_unlink(data->forks[i]);
		free(data->forks[i]);
		i++;
	}
	ft_exit(s);
}

void	ft_exit(int i)
{
	ft_free(NULL, i);
	if (i)
		write(2, "Error\n", 7);
	exit(i);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_exit(1);
	ft_free(ptr, 0);
	return (ptr);
}
