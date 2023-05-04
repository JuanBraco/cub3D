/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/04 15:13:46 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse.h"
#include "utils.h"

static void	ft_init_env(t_env *env)
{
	env->mlx = NULL;
	env->mlx_win = NULL;
	env->win_w = 0;
	env->win_h = 0;
	env->cell_size = 32;
	env->ceilcolor = -1;
	env->floorcolor = -1;
	env->wall_n_img = NULL;
	env->wall_s_img = NULL;
	env->wall_w_img = NULL;
	env->wall_e_img = NULL;
	env->map = NULL;
	env->player_o = 'X';
	env->player_pos_x = 0;
	env->player_pos_y = 0;
	env->dir_x = 0;
	env->dir_y = 0;
	env->tmp_wn_color = 0x00B3B6B7 ;
	env->tmp_ws_color = 0x00616A6B;
	env->tmp_we_color = 0x00909497;
	env->tmp_ww_color = 0x00717D7E;
}

static char	*ft_load(int ac, char **av)
{
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	if (ac != 2)
		return (printf("Error\n Usage: ./cub3D <filename>\n"), line);
	// TODO: check filename extension & access
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), line);
	ret = BUFFER_SIZE;
	buf[0] = 0;
	while (ret == BUFFER_SIZE)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (perror("Error\n"), free(line), close(fd), NULL);
		buf[ret] = 0;
		line = ft_strjoin(line, buf);
		if (!line)
			return (perror("Error\n"), close(fd), NULL);
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
