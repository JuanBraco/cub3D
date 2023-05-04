/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:48 by adcarnec          #+#    #+#             */
/*   Updated: 2023/01/24 18:05:57 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(char *src)
{
	int	len;

	len = 0;
	if (src)
	{
		while (src[len])
			len++;
	}
	return (len);
}

char	*ft_strdup(char *src)
{
	char	*copy;
	int		i;

	copy = NULL;
	if (src)
	{
		copy = malloc(sizeof(char) * (ft_strlen(src) + 1));
		if (copy)
		{
			i = -1;
			while (src[++i])
				copy[i] = src[i];
			copy[i] = 0;
		}
		else
			perror(NULL);
	}
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	char	*dest;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc(len_s1 + len_s2 + 1);
	if (!dest)
		return (NULL);
	while (++i < len_s1)
		dest[i] = s1[i];
	while (++j < len_s2)
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	return (dest);
}

int	ft_atoi(char *src)
{
	unsigned int	nb;
	int				sign;

	nb = 0;
	sign = 1;
	while (*src == ' ')
		src++;
	if (*src == '+')
		src++;
	else if (*src == '-')
	{
		sign = -1;
		src++;
	}
	while (*src >= '0' && *src <= '9')
	{
		nb = nb * 10 + (*src - '0');
		src++;
	}
	return (sign * nb);
}

/*
start included, end excluded
*/
char	*ft_substr(char *src, int start, int end)
{
	char	*res;
	int		i_src;

	if (!src || start > ft_strlen(src))
		return (NULL);
	if (start < 0)
		start = 0;
	if (end > ft_strlen(src))
		end = ft_strlen(src);
	if (end == start)
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (res)
	{
		i_src = -1;
		while (++i_src + start < end)
			res[i_src] = src[i_src + start];
		res[i_src] = 0;
	}
	return (res);
}
