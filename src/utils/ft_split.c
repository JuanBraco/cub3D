/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:44:59 by adcarnec          #+#    #+#             */
/*   Updated: 2023/01/17 12:45:52 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_countsep(char *src, char sep)
{
	int	res;
	int	i_src;

	res = 0;
	i_src = 0;
	while (src[i_src])
	{
		if (src[i_src] == sep)
			res++;
		i_src++;
	}
	return (res);
}

static int	ft_lastword(char **tab, int i_tab, char *src, int i_last)
{
	if (i_last == ft_strlen(src) - 1)
	{
		tab[i_tab] = NULL;
		return (0);
	}
	tab[i_tab] = ft_substr(src, i_last + 1, ft_strlen(src));
	if (!tab[i_tab])
		return (-1);
	tab[++i_tab] = NULL;
	return (0);
}

char	**ft_split(char *src, char sep)
{
	char	**res;
	int		i_last;
	int		i_src;
	int		i_tab;

	res = (char **)malloc(sizeof(char *) * (ft_countsep(src, sep) + 2));
	if (res)
	{
		i_last = -1;
		i_src = -1;
		i_tab = -1;
		while (src[++i_src])
		{
			if (src[i_src] == sep)
			{
				res[++i_tab] = ft_substr(src, i_last + 1, i_src);
				if (!res[i_tab])
					return (ft_freetab(res), NULL);
				i_last = i_src;
			}
		}
		if (ft_lastword(res, ++i_tab, src, i_last) == -1)
			return (ft_freetab(res), NULL);
	}
	return (res);
}
