/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:04:17 by zaissi            #+#    #+#             */
/*   Updated: 2025/02/28 21:19:02 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void     ft_free(void *ptr, int flag)
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

void    ft_exit(int i)
{
		ft_free(NULL, i);
		if (i)
			write(2, "Error\n", 7);
		exit(i);
}

void    *ft_malloc(size_t size)
{
		void    *ptr;

		ptr = malloc(size);
		if (!ptr)
				ft_exit(1);
		ft_free(ptr, 0);
		return (ptr);
}
