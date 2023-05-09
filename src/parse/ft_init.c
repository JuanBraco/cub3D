/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
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

static void	ft_init_env(t_env *env)
{
	env->mlx = NULL;
	env->mlx_win = NULL;
	env->map_w = 0;
	env->map_h = 0;
	env->ceilcolor = -1;
	env->floorcolor = -1;
	env->map = NULL;
	env->player_o = 'X';
	env->player_pos_x = 0;
	env->player_pos_y = 0;
	env->dir_x = 0;
	env->dir_y = 0;
	env->plane_x = 0;
	env->plane_y = 0;
}

static int	ft_checkcardfile(char *filename)
{
	int		fd;

	fd = -1;
	if (ft_checkext(filename, ".cub") == -1)
		return (printf("Error\nInvalid description file extension\n"), fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nopen"), fd);
	return (fd);
}

static char	*ft_load(int ac, char **av)
{
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	if (ac != 2)
		return (printf("Error\nUsage: ./cub3D <filename>\n"), line);
	fd = ft_checkcardfile(av[1]);
	if (fd == -1)
		return (line);
	ret = BUFFER_SIZE;
	buf[0] = 0;
	while (ret == BUFFER_SIZE)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (perror("Error\nread"), free(line), close(fd), NULL);
		buf[ret] = 0;
		line = ft_strjoin(line, buf);
		if (!line)
			return (perror("Error\nmalloc"), close(fd), NULL);
	}
	return (close(fd), line);
}

int	ft_init(t_env *env, int ac, char **av)
{
	char	*line;

	ft_init_env(env);
	line = ft_load(ac, av);
	if (!line)
		return (-1);
	if (ft_parse(env, ft_split(line, '\n')) == -1)
		return (free(line), -1);
	return (free(line), 0);
}
