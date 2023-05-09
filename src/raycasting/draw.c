/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:08:34 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/09 11:18:11 by jde-la-f         ###   ########.fr       */
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

/* First compute line height proportion
and then retrieve corresponding texture*/

static void	init_drawing_value(t_env *env)
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
}

static void	init_texture_draw(t_env *env)
{
	if (env->side == 0)
		env->wall_width = env->player_pos_y + env->perp_wall_dist
			* env->ray_dir_y;
	else
		env->wall_width = env->player_pos_x + env->perp_wall_dist
			* env->ray_dir_x;
	env->wall_width -= floor(env->wall_width);
	env->tex_x = env->wall_width * TEXT_WIDTH;
	if ((env->side == 0 && env->ray_dir_x > 0) || (env->side == 1
			&& env->ray_dir_y < 0))
		env->tex_x = TEXT_WIDTH - env->tex_x - 1;
	env->text_incr_y = TEXT_HEIGHT * 1.0 / env->line_height;
	env->tex_pos_y = (env->draw_start - HEIGHT / 2 + env->line_height / 2)
		* env->text_incr_y;
}

void	draw_column_slice(t_env *env, int x)
{
	int	tmp;

	tmp = 0;
	init_drawing_value(env);
	init_texture_draw(env);
	while (tmp < env->draw_start)
		my_mlx_pixel_put(env, x, tmp++, env->ceilcolor);
	while (tmp < env->draw_end)
	{
		my_mlx_pixel_put(env, x, tmp, get_color(env, env->tex_x,
				(int)env->tex_pos_y, env->texture_img));
		env->tex_pos_y += env->text_incr_y;
		tmp++;
	}
	while (tmp < HEIGHT)
		my_mlx_pixel_put(env, x, tmp++, env->floorcolor);
}
