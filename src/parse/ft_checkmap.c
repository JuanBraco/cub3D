/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/03 19:17:26 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse.h"
#include "utils.h"

int	ft_checkmap(t_env *env)
{
	printf("ceiling r %i g %i b %i\n", env->ceil_r, env->ceil_g, env->ceil_b);
	printf("floor r %i g %i b %i\n", env->floor_r, env->floor_g, env->floor_b);
	printf("map len %i\n", ft_tablen(env->map));
	return (0);
}
