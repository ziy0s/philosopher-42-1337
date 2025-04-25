/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:32:51 by zaissi            #+#    #+#             */
/*   Updated: 2025/04/25 22:48:56 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strdup(const char *s1)
{
    int             i;
    char    *p;

    i = ft_strlen(s1);
    p = malloc(i + 1);
    if (p == NULL)
            return (NULL);
    i = 0;
    while (s1[i])
    {
            p[i] = s1[i];
            i++;
    }
    p[i] = '\0';
    return (p);
}

int ft_intsize(int nbr)
{
    int size;

    size = 0;
    while (nbr)
    {
        size++;
        nbr /= 10;
    }
    size++;
    return (size);
}

char *ft_itoa(pid_t nbr)
{
    char    *str;
    int     i;
    int     sign;

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

static char     *return_value(char const *s1, char const *s2, char *p)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (s1[j])
    {
        p[j] = s1[j];
        j++;
    }
    while (s2[i])
    {
        p[j] = s2[i];
        i++;
        j++;
    }
    p[j] = '\0';
    return (p);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  i;
    size_t  j;
    char    *p;

    if (s1 == NULL && s2 == NULL)
            return (NULL);
    if (s1 == NULL)
            return (ft_strdup(s2));
    if (s2 == NULL)
            return (ft_strdup(s1));
    i = ft_strlen(s1) + ft_strlen(s2);
    j = 0;
    p = malloc(i + 1);
    if (p == NULL)
            return (NULL);
    return (return_value(s1, s2, p));
}
