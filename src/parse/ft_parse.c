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
	if (env->ceilcolor != -1 && env->floorcolor != -1) // TODO check paths to texture
		return (0);
	else
		return (-1);
}

static void	ft_gettexture(t_env *env, char *line, int *nelem)
{
	// TODO get path to texture
	(void)env;
	(void)line;
	*nelem = *nelem + 1;
}

static void	ft_getcolor(t_env *env, char *line, char elem, int *nelem)
{
	char	**tmp;
	int		len;
	int		r;
	int		g;
	int		b;

	tmp = ft_split(++line, ','); // TODO check identifier
	len = ft_tablen(tmp); // TODO check == 3
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	if (elem == 'F')
		env->floorcolor = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	else
		env->ceilcolor = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	*nelem = *nelem + 1;
	ft_freetab(tmp);
}

static int	ft_getmap(t_env *env, char **tmp)
{
	int		i;
	int		j;

	env->map = malloc(sizeof(char *) * (ft_tablen(tmp) + 1));
	if (!env->map)
		return (perror("Error\n"), -1);
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
			return (perror("Error\n"), -1);
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
	int		nelem;
	int		i;

	if (!tmp)
		return (perror("Error\n"), -1);
	nelem = 0;
	i = -1;
	while (tmp[++i] && nelem < 6)
	{
		if (ft_strlen(tmp[i]) > 0) // TODO trim
		{
			if (tmp[i][0] == 'N' || tmp[i][0] == 'S' || tmp[i][0] == 'W' || \
			tmp[i][0] == 'E' )
				ft_gettexture(env, tmp[i], &nelem);
			else if (tmp[i][0] == 'F' || tmp[i][0] == 'C')
				ft_getcolor(env, tmp[i], tmp[i][0], &nelem);
		}
	}
	if (ft_elemsset(env) == -1)
		return (printf("Error\n Missing element\n"), ft_freetab(tmp), -1);
	while (ft_strlen(tmp[i]) <= 1)
		i++;
	if (ft_getmap(env, &tmp[i]) == -1)
		return (ft_freetab(tmp), -1);
	if (ft_checkmap(env) == -1)
		return (ft_freetab(tmp), -1);
	return (ft_freetab(tmp), 0);
}
