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

/*
	int			player_x;
	int			player_y;
	char		player_o;
*/
int	ft_checkmap(t_env *env)
{
	int		i;
	int		j;
	int		n;

	printf("win h %i w %i\n", env->win_h, env->win_w);
	printf("ceiling r %i g %i b %i\n", env->ceil_r, env->ceil_g, env->ceil_b);
	printf("floor r %i g %i b %i\n", env->floor_r, env->floor_g, env->floor_b);
	i= -1;
	n = 0;
	while (env->map[++i])
	{
		printf("%s\n", env->map[i]);
		j = -1;
		while (env->map[i][++j]){
			if (env->map[i][j] == 'N' || env->map[i][j] == 'S' \
			|| env->map[i][j] == 'W' || env->map[i][j] == 'E' )
			{
				env->player_x = j;
				env->player_y = i;
				env->player_o = env->map[i][j];
				n++;
			}
		}
	}
	if (n != 1)
		return (printf("Error\n Invalid player's position\n"), -1);
	return (0);
}
