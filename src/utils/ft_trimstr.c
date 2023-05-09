/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:48 by adcarnec          #+#    #+#             */
/*   Updated: 2023/01/24 18:05:57 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_trimstr(char *src)
{
	int		i;

	if (src && ft_strlen(src) > 0)
	{
		i = ft_strlen(src);
		while (src[--i] == ' ')
			src[i] = 0;
		i = 0;
		while (src[i] == ' ')
			i++;
		return (&src[i]);
	}
	return (src);
}
