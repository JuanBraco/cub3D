/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:08:34 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/04 17:40:04 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
	char	*pixel;

	pixel = env->img.addr + (y * env->img.line_len + x * (env->img.bpp / 8));
	*(int *)pixel = color;
}

void	draw_column_slice(t_env *env, int x, int drawStart, int drawEnd, int color)
{
	int tmp = 0;
	
	while (tmp < drawStart)
	{
		my_mlx_pixel_put(env, x, tmp, env->ceilcolor);
		tmp++;
	}

	while (tmp < drawEnd)
	{
		my_mlx_pixel_put(env, x, tmp, color);
		tmp++;
	}
    while (tmp < HEIGHT)
	{
		my_mlx_pixel_put(env, x, tmp, env->floorcolor);
		tmp++;
	}
}