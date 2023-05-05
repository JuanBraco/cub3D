/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:05:40 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/05 11:02:04 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void calc_rc(t_env *env, int x)
{
    // Compute the x-coordinate of the current column in camera space
    env->camera_x = (2 * x) / (double)WIDTH - 1;

    // Compute the direction of the current ray in world space
    env->ray_dir_x = env->dir_x + env->plane_x * env->camera_x;
    env->ray_dir_y = env->dir_y + env->plane_y * env->camera_x;

    // Compute the integer coordinates of the current cell in the map
    env->map_x = env->player_pos_x;
    env->map_y = env->player_pos_y;

    // Compute the distances to the first vertical and horizontal walls
    if (env->ray_dir_x == 0) 
        env->delta_dist_x = INT_MAX;
    else 
        env->delta_dist_x = fabs(1 / env->ray_dir_x);
    if (env->ray_dir_y == 0) 
        env->delta_dist_y = INT_MAX;
    else
        env->delta_dist_y = fabs(1 / env->ray_dir_y);

    // Determine the direction to step in x and y
    // Compute the initial side distances
    if (env->ray_dir_x < 0) 
    {
        env->step_x = -1;
        env->side_dist_x = (env->player_pos_x - env->map_x) * env->delta_dist_x;
    }
    else
    {
        env->step_x = 1;
        env->side_dist_x = (env->map_x + 1.0 - env->player_pos_x) * env->delta_dist_x;
    }
    if (env->ray_dir_y < 0)
    {
        env->step_y = -1;
        env->side_dist_y = (env->player_pos_y - env->map_y) * env->delta_dist_y;
    }
    else
    {
        env->step_y = 1;			
        env->side_dist_y = (env->map_y + 1.0 - env->player_pos_y) * env->delta_dist_y;
    }
}

void compute_drawing(t_env *env)
{
    // Perform the DDA algorithm to find the closest wall hit by the ray
		env->hit = 0;
		env->side = 0;
		while (env->hit == 0)
		{
			// Move to the next cell in the closest direction
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

			// Check if the current cell contains a wall
			if (env->map[env->map_x][env->map_y] == '1')
				env->hit = 1;
		}

		// Compute the perpendicular distance to the wall
		if (env->side == 0)
			env->perp_wall_dist = (env->map_x - env->player_pos_x + (1 - env->step_x) / 2) / env->ray_dir_x;
		else
			env->perp_wall_dist = (env->map_y - env->player_pos_y + (1 - env->step_y) / 2) / env->ray_dir_y;

		// Compute the height of the wall slice on the screen
		env->line_height = (int)(HEIGHT / env->perp_wall_dist);

		// Compute the starting and ending positions of the wall slice on the screen
		env->draw_start = -env->line_height / 2 + HEIGHT / 2;
		if (env->draw_start < 0)
			env->draw_start = 0;
	    env->draw_end = env->line_height / 2 + HEIGHT / 2;
		if (env->draw_end >= HEIGHT)
			env->draw_end = HEIGHT - 1;

		if (env->side == 0 && env->ray_dir_x < 0)
			env->color = 0x00880000;
		if (env->side == 0 && env->ray_dir_x > 0)
			env->color = 0x00008800;
		if (env->side == 1 && env->ray_dir_y < 0)
			env->color = 0x00000088;
		if (env->side == 1 && env->ray_dir_y > 0)
			env->color = 0x00FFFFFF;
        
}

int	close_game(t_env *env)
{
    mlx_destroy_image(env->mlx, env->img.mlx_img);
	mlx_destroy_window(env->mlx, env->mlx_win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
    if (env->map)
			ft_freetab(env->map);
	exit (0);
}


void	graphic_error(t_env *env, char *message)
{
	ft_putstr_fd(message, 2);
	mlx_destroy_image(env->mlx, env->img.mlx_img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit (EXIT_FAILURE);
}

int	render(t_env *env)
{
	raycasting(env);
    mlx_put_image_to_window(env->mlx, env->mlx_win, env->img.mlx_img,
		0, 0);
	return (0);
}

int raycasting(t_env *env)
{
	int x = 0;
	while (x < WIDTH)
	{
		calc_rc(env, x);
        compute_drawing(env);
        draw_column_slice(env, x, env->draw_start, env->draw_end, env->color);
		x++;
	}
    return (0);
}