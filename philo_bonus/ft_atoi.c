/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:00:27 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/12 21:01:05 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == '"')
		return (c);
	return (0);
}

static int	check(size_t i, int j)
{
	if (i > INT_MAX && j > 0)
		return (0);
	else if (i > 2147483648 && j < 0)
		return (0);
	return (1);
}

static int	is_not_digit(char s)
{
	if (!ft_isdigit(s))
		return (0);
	return (1);
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
		if (!is_not_digit(str[i]))
			return (0);
		res = res * 10 + str[i] - 48;
		if (!check(res, j))
			return (0);
		i++;
	}
	if (j < 0)
		res = res * (-1);
	return (res);
}
