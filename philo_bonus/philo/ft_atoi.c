/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:19:33 by zaissi            #+#    #+#             */
/*   Updated: 2025/03/02 17:57:04 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == '"')
		return (c);
	return (0);
}

static void	check(size_t i, int j)
{
	if (i > INT_MAX && j > 0)
		error();
	else if (i > 2147483648 && j < 0)
		error();
}

static void	is_not_digit(char s)
{
	if (!ft_isdigit(s))
		error(NULL, NULL);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				j;
	size_t			res;

	i = 0;
	j = 1;
	res = 0;
	while (str[i])
	{
		is_not_digit(str[i]);
		res = res * 10 + str[i] - 48;
		check(res, j);
		i++;
	}
	if (j < 0)
		res = res * (-1);
	return (res);
}
