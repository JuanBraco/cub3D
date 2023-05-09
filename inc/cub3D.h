/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:22:01 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/09 11:21:15 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "utils.h"
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_L 65361
# define KEY_R 65363

# define WIDTH (1940)
# define HEIGHT (1280)

# define TEXT_WIDTH (128)
# define TEXT_HEIGHT (128)

typedef struct s_img
{
	int					line_len;
	int					endian;
	int					bpp;
	void				*mlx_img;
	char				*addr;
	char				*path;
	int					width;
	int					height;
}						t_img;

typedef struct s_env	t_env;

struct					s_env
{
	void				*mlx;
	void				*mlx_win;
	t_img				img[5];
	t_img				minimap;
	int					m_fact;

	int					map_w;
	int					map_h;
	int					cell_size;
	char				**map;
	char				player_o;
	int					ceilcolor;
	int					floorcolor;
	void				*wall_n_img;
	void				*wall_s_img;
	void				*wall_w_img;
	void				*wall_e_img;
	int					tmp_wn_color;
	int					tmp_ws_color;
	int					tmp_we_color;
	int					tmp_ww_color;

	double				player_pos_x;
	double				player_pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				ray_incr;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				side_dist_x;
	double				side_dist_y;
	int					hit;
	int					side;
	double				perp_wall_dist;

	int					color;
	int					draw_start;
	int					draw_end;
	double				wall_width;
	double				move_speed;
	double				cam_speed;
	int					texture_img;
	int					line_height;
	double				text_incr_y;
	double				tex_pos_y;
	int					tex_x;
	int					tex_y;
};

int						ft_init(t_env *env, int ac, char **av);
void					ft_free(t_env *env);

/* RAYCASTING */

int						raycasting(t_env *env);
int						render(t_env *env);
int						close_management(t_env *env);

/* DRAW.C */

void					my_mlx_pixel_put(t_env *env, int x, int y, int color);
void					draw_column_slice(t_env *env, int x);

int						key_hook(int key, t_env *env);
int						mouse_hook(int x, int y, t_env *env);
void					draw_minimap(t_env *env, int x, int y, int color);

void					minimaping(t_env *env);

#endif