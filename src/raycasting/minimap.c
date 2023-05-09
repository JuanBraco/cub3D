/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:11 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/09 11:24:58 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put_minimap(t_env *env, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > HEIGHT - 1 || x < 0 || x > WIDTH - 1)
		return ;
	pixel = env->minimap.addr + (y * env->minimap.line_len + x
			* (env->minimap.bpp / 8));
	*(int *)pixel = color;
}

void	draw_minimap(t_env *env, int y, int x, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < env->m_fact)
	{
		j = 0;
		while (j < env->m_fact)
		{
			my_mlx_pixel_put_minimap(env, y + i, x + j, color);
			j++;
		}
		i++;
	}
}

void	minimaping(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (env->map_w > env->map_h)
		env->m_fact = floor(((double)WIDTH / 7.0) / (double)env->map_w);
	else
		env->m_fact = floor(((double)HEIGHT / 7.0) / (double)env->map_h);
	while (env->map[i])
	{
		j = 0;
		while (env->map[i][j])
		{
            draw_minimap(env, j * env->m_fact, i * env->m_fact, 0x000000);
			if (env->map[i][j] == '1')
				draw_minimap(env, j * env->m_fact, i * env->m_fact, 0xFFFFFF);
			draw_minimap(env, (int)env->player_pos_y * env->m_fact,
				(int)env->player_pos_x * env->m_fact, 0xFF);
			j++;
		}
		i++;
	}
}