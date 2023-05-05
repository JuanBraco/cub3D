/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:48 by adcarnec          #+#    #+#             */
/*   Updated: 2023/01/24 18:05:57 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_freetab(char **tab)
{
	int	i_tab;

	i_tab = 0;
	while (tab[i_tab])
	{
		free(tab[i_tab]);
		tab[i_tab] = NULL;
		i_tab++;
	}
	free(tab);
	tab = NULL;
}

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	if (tab && *tab)
	{
		while (tab[len])
			len++;
	}
	return (len);
}

char	**ft_tabdup(char **tab)
{
	char	**copy;
	int		i;

	copy = NULL;
	if (tab && *tab)
	{
		copy = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
		if (copy)	
		{
			i = -1;
			while (tab[++i])
			{
				copy[i] = ft_strdup(tab[i]);
				if (!copy[i])
					return (ft_freetab(copy), NULL);
			}
			copy[i] = NULL;
		}
	}
	return (copy);
}

void	ft_printtab(char **tab)
{
	int	i;

	i = -1;
	if (tab && *tab)
	{
		printf("\n");
		while (tab[++i])
			printf("%s\n", tab[i]);
	}
}
