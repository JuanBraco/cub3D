/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:48 by adcarnec          #+#    #+#             */
/*   Updated: 2023/01/24 18:05:57 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcmp(const char *src1, const char *src2)
{
	int	i;

	if (!src1 && !src2)
		return (0);
	if (src1 && src2)
	{
		i = 0;
		while (src1[i] && src2[i])
		{
			if (src1[i] != src2[i])
				return (src1[i] - src2[i]);
			i++;
		}
		return (src1[i] - src2[i]);
	}
	return (-1);
}

int	ft_checkext(char *file, char *ext)
{
	int		ret;

	ret = -1;
	if (file && ext)
	{
		if (ft_strcmp(&file[ft_strlen(file) - ft_strlen(ext)], ext) == 0)
			ret = 0;
	}
	return (ret);
}
