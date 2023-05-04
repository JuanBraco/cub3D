/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:22:01 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/03 19:22:04 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_env t_env;

struct s_env {
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	int			cell_size;
	int			player_x;
	int			player_y;
	char		player_o;
	char		**map;
	int			ceil_r;
	int			ceil_g;
	int			ceil_b;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	void		*wall_n_img;
	void		*wall_s_img;
	void		*wall_w_img;
	void		*wall_e_img;
	int			tmp_wn_r;
	int			tmp_wn_g;
	int			tmp_wn_b;
	int			tmp_ws_r;
	int			tmp_ws_g;
	int			tmp_ws_b;
	int			tmp_we_r;
	int			tmp_we_g;
	int			tmp_we_b;
	int			tmp_ww_r;
	int			tmp_ww_g;
	int			tmp_ww_b;
};

int ft_init(t_env *env, int ac, char **av);

#endif
