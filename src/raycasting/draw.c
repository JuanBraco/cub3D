/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:08:34 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/05 16:05:11 by jde-la-f         ###   ########.fr       */
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

void	draw_column_slice(t_env *env, int x)
{
	int	tmp;

	tmp = 0;
	if (env->side == 0 && env->ray_dir_x < 0)
		env->color = 1;
	else if (env->side == 0 && env->ray_dir_x > 0)
		env->color = 1;
	else if (env->side == 1 && env->ray_dir_y < 0)
		env->color = 1;
	else if (env->side == 1 && env->ray_dir_y > 0)
		env->color = 1;
	while (tmp < env->draw_start)
		my_mlx_pixel_put(env, x, tmp++, env->ceilcolor);
	while (tmp < env->draw_end)
	{
		my_mlx_pixel_put(env, x, tmp, get_color(env, x, tmp, env->color));
		tmp++;
	}
	while (tmp < HEIGHT)
		my_mlx_pixel_put(env, x, tmp++, env->floorcolor);
}
