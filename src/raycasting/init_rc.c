/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:05:40 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/04 15:53:02 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void    ft_init_rc(t_env *env)
{
    env->player_pos_x = 22;
    env->player_pos_y = 12;  //x and y start position
    env->dir_x = -1;
    env->dir_y = 0; //initial direction vector
    env->plane_x = 0;
    env->plane_y = 0.66; //the 2d raycaster version of camera plane

    /*double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame*/
}

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

void compute_drawing(t_env *env, int x)
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
			if (worldMap[env->map_x][env->map_y] > 0)
				env->hit = 1;
		}

		// Compute the perpendicular distance to the wall
		if (env->side == 0)
			env->perp_wall_dist = (env->map_x - env->player_pos_x + (1 - env->step_x) / 2) / env->ray_dir_x;
		else
			env->perp_wall_dist = (env->map_y - env->player_pos_y + (1 - env->step_y) / 2) / env->ray_dir_y;

		// Compute the height of the wall slice on the screen
		int lineHeight = (int)(HEIGHT / env->perp_wall_dist);

		// Compute the starting and ending positions of the wall slice on the screen
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

      switch(worldMap[env->map_x][env->map_y])
      {
        case 1:  env->color = 0x00880000;    break; //red
        case 2:  env->color = 0x00006600;  break; //green
        case 3:  env->color = 0x00006600;   break; //blue
        case 4:  env->color = 0x00FFFFFF;  break; //white
        default: env->color = 0x0000FFFF; break; //yellow
      }

		// Draw the wall slice on the screen
		draw_line(env, x, drawStart, drawEnd, env->color);
}

void raycasting(t_env *env)
{
    env->mlx = mlx_init();
    env->mlx_win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "cub3d");
    env->img.mlx_img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    env->img.addr = mlx_get_data_addr(env->img.mlx_img, &env->img.bpp,
    &env->img.line_len, &env->img.endian);
	
	ft_init_rc(env);

	// Loop over all the columns of the screen
	int x = 0;
	while (x < WIDTH)
	{
		calc_rc(env, x);
        compute_drawing(env, x);
		x++;
	}

	//my_mlx_pixel_put(&env, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img.mlx_img,
			0, 0);
	mlx_loop(env->mlx);
}