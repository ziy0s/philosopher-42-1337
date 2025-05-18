/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:08:47 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/16 11:08:50 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_intsize(int nbr)
{
	int	size;

	size = 0;
	while (nbr)
	{
		size++;
		nbr /= 10;
	}
	size++;
	return (size);
}

char	*ft_itoa(pid_t nbr)
{
	char	*str;
	int		i;
	int		sign;

	sign = 1;
	if (nbr < 0)
		sign = -1;
	str = ft_malloc(sizeof(char) * (ft_intsize(nbr) + 1));
	i = 0;
	if (nbr < 0)
		str[i++] = '-';
	if (nbr == 0)
		str[i++] = '0';
	while (nbr)
	{
		str[i++] = (nbr % 10) * sign + '0';
		nbr /= 10;
	}
	str[i] = '\0';
	return (str);
}
