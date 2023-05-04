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

static int	ft_init_mlx(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->win_w = 0;
	env->win_h = 0;
	env->cell_size = 32;
	env->ceil_r = 133;
	env->ceil_g = 193;
	env->ceil_b = 233;
	env->floor_r = 126;
	env->floor_g = 81;
	env->floor_b = 9;
	env->wall_n_img = NULL;
	env->wall_s_img = NULL;
	env->wall_w_img = NULL;
	env->wall_e_img = NULL;
}

static int	ft_init_map(t_env *env)
{
	env->player_x = 0;
	env->player_y = 0;
	env->player_o = 'N';
	env->map = NULL;
}

static int	ft_init_tmpcolor(t_env *env)
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

static int	ft_errmg(int ac, char **av){
	if (ac != 2)
		return (printf("Error\n Usage: ./cub3D <filename>\n"), -1);
	// TODO: check filename extension
	// TODO: load file
	return (0);
}

int	ft_init(t_env *env, int ac, char **av)
{
	if (ft_errmg(ac, av) == -1)
		return (-1);
	env = malloc(sizeof(t_env));
	if (!env)
		return (perror("Error\n"), -1);
	ft_init_mlx(env);
	ft_init_map(env);
	ft_init_tmpcolor(env);
	return (0);
}
