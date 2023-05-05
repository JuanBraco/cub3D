/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:08:34 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/05 16:55:50 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > HEIGHT - 1 || x < 0 || x > WIDTH - 1)
		return ;
	pixel = env->img[0].addr + (y * env->img[0].line_len + x * (env->img[0].bpp
				/ 8));
	*(int *)pixel = color;
}

int	get_color(t_env *env, int x, int y, int i)
{
	return (*(int *)(env->img[i].addr + (y * env->img[i].line_len + x
			* (env->img[i].bpp / 8))));
}

static void	compute_drawing_value(t_env *env)
{
	env->line_height = (int)(HEIGHT / env->perp_wall_dist);
	env->draw_start = -env->line_height / 2 + HEIGHT / 2;
	if (env->draw_start < 0)
		env->draw_start = 0;
	env->draw_end = env->line_height / 2 + HEIGHT / 2;
	if (env->draw_end >= HEIGHT)
		env->draw_end = HEIGHT - 1;
	if (env->side == 0 && env->ray_dir_x < 0)
		env->texture_img = 1;
	else if (env->side == 0 && env->ray_dir_x > 0)
		env->texture_img = 2;
	else if (env->side == 1 && env->ray_dir_y < 0)
		env->texture_img = 3;
	else if (env->side == 1 && env->ray_dir_y > 0)
		env->texture_img = 4;
	if (env->side == 0)
		env->wall_height = env->player_pos_y + env->perp_wall_dist * env->ray_dir_y;
	else
		env->wall_height = env->player_pos_x + env->perp_wall_dist * env->ray_dir_x;
	env->wall_height -= floor(env->wall_height);
	env->tex_x = env->wall_height * 128;
	if (env->side == 0 && env->ray_dir_x > 0)
		env->tex_x = 128 - env->tex_x - 1;
	if (env->side == 1 && env->ray_dir_y < 0)
		env->tex_x = 128 - env->tex_x - 1;
	env->incr = 1.0 * 128 / env->line_height;
	env->tex_pos = (env->draw_start - HEIGHT / 2
			+ env->line_height / 2) * env->incr;
}

void	draw_column_slice(t_env *env, int x)
{
	int	tmp;

	tmp = 0;

	compute_drawing_value(env);
	while (tmp < env->draw_start)
		my_mlx_pixel_put(env, x, tmp++, env->ceilcolor);
	while (tmp < env->draw_end)
	{
		env->tex_y = (int)env->tex_pos & (128 - 1);
		env->tex_pos += env->incr;
		my_mlx_pixel_put(env, x, tmp, get_color(env, env->tex_x, env->tex_y, env->texture_img));
		tmp++;
	}
	while (tmp < HEIGHT)
		my_mlx_pixel_put(env, x, tmp++, env->floorcolor);
}
