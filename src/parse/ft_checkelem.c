/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkelem.c                                     :+:      :+:    :+:   */
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

static void	ft_settexture(t_env *env, char *line, int *nelem, int index)
{
	env->img[index].path = line;
	*nelem = *nelem + 1;
}

static int	ft_gettexture(t_env *env, char *line, int *nelem)
{
	int		fd;
	int		i;

	if (ft_strlen(line) > 7)
	{
		i = 2;
		while (line[i] == ' ')
			i++;
		if (ft_checkext(&line[i], ".xpm") == -1)
			return (printf("Error\nInvalid image extension\n"), -1);
		fd = open(&line[i], O_RDONLY);
		if (fd == -1)
			return (perror("Error\nopen"), -1);
		if (close(fd) == -1)
			return (perror("Error\nclose"), -1);
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			return (ft_settexture(env, &line[i], nelem, 1), 0);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			return (ft_settexture(env, &line[i], nelem, 2), 0);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			return (ft_settexture(env, &line[i], nelem, 3), 0);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			return (ft_settexture(env, &line[i], nelem, 4), 0);
	}
	return (printf("Error\nInvalid texture identifier\n"), -1);
}

static int	ft_getcolor(t_env *env, char *line, char elem, int *nelem)
{
	char	**tmp;

	if (ft_strlen(line) < 7 || (line[0] != 'F' && line[0] != 'C') || \
	line[1] != ' ')
		return (printf("Error\nInvalid color identifier\n"), -1);
	tmp = ft_split(++line, ',');
	if (ft_tablen(tmp) != 3)
		return (printf("Error\nInvalid color identifier\n"), -1);
	if (ft_atoi(tmp[0]) < 0 || ft_atoi(tmp[0]) > 255 || ft_atoi(tmp[1]) < 0 || \
	ft_atoi(tmp[1]) > 255 || ft_atoi(tmp[2]) < 0 || ft_atoi(tmp[2]) > 255)
		return (printf("Error\nInvalid color identifier\n"), ft_freetab(tmp), -1);
	if (elem == 'F')
		env->floorcolor = ((ft_atoi(tmp[0]) & 0xff) << 16) + \
		((ft_atoi(tmp[1]) & 0xff) << 8) + (ft_atoi(tmp[2]) & 0xff);
	else
		env->ceilcolor = ((ft_atoi(tmp[0]) & 0xff) << 16) + \
		((ft_atoi(tmp[1]) & 0xff) << 8) + (ft_atoi(tmp[2]) & 0xff);
	return (*nelem = *nelem + 1, ft_freetab(tmp), 0);
}

int	ft_checkelem(t_env *env, char **tmp)
{
	char	*line;
	int		nelem;
	int		i;

	nelem = 0;
	i = -1;
	while (tmp[++i] && nelem < 6)
	{
		line = ft_trimstr(tmp[i]);
		if (ft_strlen(line) > 0)
		{
			if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' \
			|| line[0] == 'E')
			{
				if (ft_gettexture(env, line, &nelem) == -1)
					return (ft_freetab(tmp), -1);
			}
			else if (line[0] == 'F' || line[0] == 'C')
				if (ft_getcolor(env, line, line[0], &nelem) == -1)
					return (ft_freetab(tmp), -1);
		}
	}
	return (i);
}
