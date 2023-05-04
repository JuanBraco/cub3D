/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
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

static int	ft_elemsset(t_env *env)
{
	if (env->floor_r != -1 && env->floor_g  != -1 && env->floor_b != -1 \
	&& env->ceil_r != -1 && env->ceil_g != -1 && env->ceil_b != -1)
		return (0);
	else
		return (-1);
	// TODO check paths to texture
}

static void	ft_gettexture(t_env *env, char *line, int *nelem)
{
	// TODO get path to texture
	(void)env;
	(void)line;
	*nelem = *nelem + 1;
}

static void	ft_getcolor(t_env *env, char *line, int *nelem)
{
	char	**tmp;
	char	c;
	int		len;

	c = line[0];
	tmp = ft_split(++line, ',');
	len = ft_tablen(tmp); // TODO check == 3
	if (c == 'F'){
		env->floor_r = ft_atoi(tmp[0]);
		env->floor_g = ft_atoi(tmp[1]);
		env->floor_b = ft_atoi(tmp[2]);
	}
	else
	{
		env->ceil_r = ft_atoi(tmp[0]);
		env->ceil_g = ft_atoi(tmp[1]);
		env->ceil_b = ft_atoi(tmp[2]);
	}
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
	while (tmp[++i]){
		if (env->win_w < ft_strlen(tmp[i]))
			env->win_w = ft_strlen(tmp[i]);
	}
	env->win_h = i;
	i = -1;
	while (tmp[++i]){
		env->map[i] = malloc(sizeof(char) * (env->win_w + 1));
		if (!env->map[i])
			return (perror("Error\n"), -1);
		j = -1;
		while (tmp[i][++j])
			env->map[i][j] = tmp[i][j];
		while (j < env->win_w)
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
		if (ft_strlen(tmp[i]) > 0)  // TODO trim
		{
			if (tmp[i][0] == 'N' || tmp[i][0] == 'S' || tmp[i][0] == 'W' || \
			tmp[i][0] == 'E' )
				ft_gettexture(env, tmp[i], &nelem);
			else if (tmp[i][0] == 'F' || tmp[i][0] == 'C')
				ft_getcolor(env, tmp[i], &nelem);
		}
	}
	if (ft_elemsset(env) == -1)
		return (printf("Error\n Missing element\n"), ft_freetab(tmp), -1);
	while (ft_strlen(tmp[i]) <= 1)
		i++;
	if (ft_getmap(env, &tmp[i]) == -1)
		return (ft_freetab(tmp), -1);
	return (ft_checkmap(env), ft_freetab(tmp), 0);
}
