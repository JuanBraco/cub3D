/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkwall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/04 15:13:41 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse.h"
#include "utils.h"

static int	ft_isclosed(char **map, int width, int height)
{
	int		i;
	int		j;

	j = -1;
	while (map[0][++j])
		if (map[0][j] == 'C')
			return (-1);
	j = -1;
	while (map[height - 1][++j])
		if (map[height - 1][j] == 'C')
			return (-1);
	i = -1;
	while (map[++i] && map[i][0])
		if (map[i][0] == 'C')
			return (-1);
	i = -1;
	while (map[++i] && map[i][width - 1])
		if (map[i][width - 1] == 'C')
			return (-1);
	return (0);
}

static int	ft_nblank(char **map, int *start_x, int *start_y)
{
	int		n;
	int		i;
	int		j;

	n = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'B')
			{
				n++;
				*start_x = j;
				*start_y = i;
			}
		}
	}
	return (n);
}

static void	ft_fill(t_env *env, char **map, int start_x, int start_y)
{
	map[start_y][start_x] = 'C';
	if (start_y > 0 && (map[start_y - 1][start_x] == '0' || \
	map[start_y - 1][start_x] == ' '))
		map[start_y - 1][start_x] = 'B';
	if (start_y < env->map_h - 1 && (map[start_y + 1][start_x] == '0' || \
	map[start_y + 1][start_x] == ' '))
		map[start_y + 1][start_x] = 'B';
	if (start_x < env->map_w - 1 && (map[start_y][start_x + 1] == '0' || \
	map[start_y][start_x + 1] == ' '))
		map[start_y][start_x + 1] = 'B';
	if (start_x > 0 && (map[start_y][start_x - 1] == '0' || \
	map[start_y][start_x - 1] == ' '))
		map[start_y][start_x - 1] = 'B';
}

int	ft_checkwall(t_env *env)
{
	char	**map;
	int		start_x;
	int		start_y;

	map = ft_tabdup(env->map);
	if (!map)
		return(perror("Error\n"), -1);
	start_x = -1;
	start_y = -1;
	ft_fill(env, map, env->player_pos_y, env->player_pos_x);
	while (ft_nblank(map, &start_x, &start_y) > 0)
		ft_fill(env, map, start_x, start_y);
	if (ft_isclosed(map, env->map_w, env->map_h) == -1)
		return (printf("Error\nMap is not closed\n"), ft_freetab(map), -1);
	return (ft_freetab(map), 0);
}
