/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:48:03 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/13 18:43:22 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#define MAX 2000000

static void	my_ft_free(void *ptr, int flag)
{
	static void		*lst[MAX];
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

int	ft_exit(int i)
{
	my_ft_free(NULL, i);
	if (i)
		write(2, "Error\n", 7);
	exit (i);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_exit(1), NULL);
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
