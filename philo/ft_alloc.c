/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:04:17 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/02 10:20:17 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	my_ft_free(void *ptr, int flag)
{
	static void		*lst[INT_MAX];
	static int		i;
	int				j;

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

int	ft_exit(int i, t_data *ptr)
{
	int	j;

	j = 0;
	if (ptr)
	{
		pthread_mutex_destroy(&ptr->write_m);
		pthread_mutex_destroy(&ptr->protect);
		while (j < ptr->num_philo)
		{
			pthread_mutex_destroy(ptr->philo[j].l_fork);
			pthread_mutex_destroy(ptr->philo[j].r_fork);
			pthread_mutex_destroy(&ptr->philo[j].eat_mutex);
			pthread_mutex_destroy(&ptr->forks[j]);
			j++;
		}
	}
	my_ft_free(NULL, i);
	if (i)
		write(2, "Error\n", 7);
	return (i);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_exit(1, NULL), NULL);
	my_ft_free(ptr, 0);
	return (ptr);
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
