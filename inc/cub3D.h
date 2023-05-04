/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:22:01 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/04 15:50:06 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>

# define WIDTH (640)
# define HEIGHT (480)

typedef struct s_img
{
	int		line_len;
	int		endian;
	int		bpp;
	void	*mlx_img;
	char	*addr;
}			t_img;

typedef struct s_env	t_env;

struct s_env {
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	
	int			win_w;
	int			win_h;
	int			cell_size;
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

	double			player_pos_x;
	double			player_pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				hit;
	int				side;
	double			perp_wall_dist;

	int				color;
};

int		ft_init(t_env *env, int ac, char **av);
void	ft_free(t_env *env);

/* RAYCASTING */

void    ft_init_rc(t_env *env);
void	calc_rc(t_env *env, int x);
void raycasting(t_env *env);

/* DRAW.C */

void	my_mlx_pixel_put(t_env *env, int x, int y, int color);
void	draw_line(t_env *env, int x, int drawStart, int drawEnd, int color);

#endif
