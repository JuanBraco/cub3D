/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/05 08:37:51 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse.h"
#include "utils.h"

static void	ft_setorientation(t_env *env, char o)
{
	env->player_o = o;
	if (o == 'N')
	{
		env->dir_x = -1;
		env->plane_y = 0.66;
	}
	else if (o == 'S')
	{
		env->dir_x = 1;
		env->plane_y = -0.66;
	}
	else if (o == 'E')
	{
		env->dir_y = 1;
		env->plane_x = 0.66;
	}
	else if (o == 'W')
	{
		env->dir_y = -1;
		env->plane_x = -0.66;
	}
}

static void	ft_setplayer(t_env *env, char o, int x, int y)
{
	env->player_o = o;
	ft_setorientation(env, o);
	env->player_pos_x = x;
	env->player_pos_y = y;
}

int	ft_checkmap(t_env *env)
{
	int		i;
	int		j;
	int		n;

	i = -1;
	n = 0;
	while (env->map[++i])
	{
		j = -1;
		while (env->map[i][++j])
		{
			if (env->map[i][j] == 'N' || env->map[i][j] == 'S' \
			|| env->map[i][j] == 'W' || env->map[i][j] == 'E' )
			{
				ft_setplayer(env, env->map[i][j], i, j);
				n++;
			}
			else if (env->map[i][j] != '0' && env->map[i][j] != '1' \
			&& env->map[i][j] != ' ')
				return (printf("Error\nInvalid map character\n"), -1);
		}
	}
	if (n != 1)
		return (printf("Error\nInvalid player's position\n"), -1);
	return (ft_checkwall(env));
}
