/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/04 17:43:33 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse.h"
#include "utils.h"

static int	ft_elemsset(t_env *env)
{
	if (env->ceilcolor != -1 && env->floorcolor != -1 && \
	ft_strlen(env->img[1].path) > 5 && ft_strlen(env->img[2].path) > 5 && \
	ft_strlen(env->img[3].path) > 5 && ft_strlen(env->img[4].path) > 5)
		return (0);
	else
		return (-1);
}

static int	ft_getmap(t_env *env, char **tmp)
{
	int		i;
	int		j;

	env->map = malloc(sizeof(char *) * (ft_tablen(tmp) + 1));
	if (!env->map)
		return (perror("Error\nmalloc"), -1);
	i = -1;
	while (tmp[++i])
		if (env->map_w < ft_strlen(tmp[i]))
			env->map_w = ft_strlen(tmp[i]);
	env->map_h = i;
	i = -1;
	while (tmp[++i])
	{
		env->map[i] = malloc(sizeof(char) * (env->map_w + 1));
		if (!env->map[i])
			return (perror("Error\nmalloc"), -1);
		j = -1;
		while (tmp[i][++j])
			env->map[i][j] = tmp[i][j];
		while (j < env->map_w)
			env->map[i][j++] = '0';
		env->map[i][j] = 0;
	}
	return (env->map[i] = NULL, 0);
}

int	ft_parse(t_env *env, char **tmp)
{
	int		i;

	if (!tmp)
		return (perror("Error\nmalloc"), -1);
	i = ft_checkelem(env, tmp);
	if (i == -1)
		return (-1);
	if (ft_elemsset(env) == -1)
		return (printf("Error\nMissing element\n"), ft_freetab(tmp), -1);
	while (ft_strlen(tmp[i]) <= 1)
		i++;
	if (ft_getmap(env, &tmp[i]) == -1 || ft_checkmap(env) == -1)
		return (ft_freetab(tmp), -1);
	return (ft_freetab(tmp), 0);
}
