/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
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

static void	ft_init_mlx(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->win_w = 0;
	env->win_h = 0;
	env->cell_size = 32;
	env->ceil_r = -1;
	env->ceil_g = -1;
	env->ceil_b = -1;
	env->floor_r = -1;
	env->floor_g = -1;
	env->floor_b = -1;
	env->wall_n_img = NULL;
	env->wall_s_img = NULL;
	env->wall_w_img = NULL;
	env->wall_e_img = NULL;
}

static void	ft_init_map(t_env *env)
{
	env->player_x = 0;
	env->player_y = 0;
	env->player_o = 'N';
	env->map = NULL;
}

static void	ft_init_tmpcolor(t_env *env)
{
	env->tmp_wn_r = 179;
	env->tmp_wn_g = 182;
	env->tmp_wn_b = 183;
	env->tmp_ws_r = 97;
	env->tmp_ws_g = 106;
	env->tmp_ws_b = 107;
	env->tmp_we_r = 144;
	env->tmp_we_g = 148;
	env->tmp_we_b = 151;
	env->tmp_ww_r = 113;
	env->tmp_ww_g = 125;
	env->tmp_ww_b = 126;
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

	line = ft_load(ac, av);
	if (!line)
		return (-1);
	ft_init_mlx(env);
	ft_init_map(env);
	ft_init_tmpcolor(env);
	if (ft_parse(env, ft_split(line, '\n')) == -1)
		return (free(line), -1);
	return (free(line), 0);
}
