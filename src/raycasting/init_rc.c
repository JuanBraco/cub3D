/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:05:40 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/09 11:18:20 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	calc_delta(t_env *env)
{
	env->hit = 0;
	env->side = 0;
	if (env->ray_dir_x < 0)
	{
		env->step_x = -1;
		env->side_dist_x = (env->player_pos_x - env->map_x) * env->delta_dist_x;
	}
	else
	{
		env->step_x = 1;
		env->side_dist_x = (env->map_x + 1.0 - env->player_pos_x)
			* env->delta_dist_x;
	}
	if (env->ray_dir_y < 0)
	{
		env->step_y = -1;
		env->side_dist_y = (env->player_pos_y - env->map_y) * env->delta_dist_y;
	}
	else
	{
		env->step_y = 1;
		env->side_dist_y = (env->map_y + 1.0 - env->player_pos_y)
			* env->delta_dist_y;
	}
}

static void	find_wall_hit(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->side_dist_x < env->side_dist_y)
		{
			env->side_dist_x += env->delta_dist_x;
			env->map_x += env->step_x;
			env->side = 0;
		}
		else
		{
			env->side_dist_y += env->delta_dist_y;
			env->map_y += env->step_y;
			env->side = 1;
		}
		if (env->map[env->map_x][env->map_y] == '1')
			env->hit = 1;
	}
	if (env->side == 0)
		env->perp_wall_dist = (env->side_dist_x - env->delta_dist_x);
	else
		env->perp_wall_dist = (env->side_dist_y - env->delta_dist_y);
}

/* ray_incr is the value from
	-1 to 1 that represent each ray launched on the view plan*/

int	raycasting(t_env *env)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		env->ray_incr = (2 * x) / (double)WIDTH - 1;
		env->ray_dir_x = env->dir_x + env->plane_x * env->ray_incr;
		env->ray_dir_y = env->dir_y + env->plane_y * env->ray_incr;
		env->map_x = (int)env->player_pos_x;
		env->map_y = (int)env->player_pos_y;
		if (env->ray_dir_x == 0)
			env->delta_dist_x = INT_MAX;
		else
			env->delta_dist_x = fabs(1 / env->ray_dir_x);
		if (env->ray_dir_y == 0)
			env->delta_dist_y = INT_MAX;
		else
			env->delta_dist_y = fabs(1 / env->ray_dir_y);
		calc_delta(env);
		find_wall_hit(env);
		draw_column_slice(env, x);
		x++;
	}
	return (0);
}

int	render(t_env *env)
{
	raycasting(env);
	minimaping(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img[0].mlx_img, 0, 0);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->minimap.mlx_img, 10,
			10);
	return (0);
}
