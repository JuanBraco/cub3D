/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:16:37 by jde-la-f          #+#    #+#             */
/*   Updated: 2023/05/05 10:38:49 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    move(t_env *env, double move_x, double move_y, int dir)
{
    if (dir == 1)
    {
        //if (env->map[(int)env->player_pos_y][(int)(env->player_pos_x + move_x)] != '1')
            env->player_pos_x += move_x;
        //if (env->map[(int)(env->player_pos_y + move_y)][(int)env->player_pos_x] != '1')
            env->player_pos_y += move_y;   
    }
    if (dir == -1)
    {
        //if (env->map[(int)env->player_pos_y][(int)(env->player_pos_x - move_x)] != '1')
            env->player_pos_x -= move_x;
        //if (env->map[(int)(env->player_pos_y - move_y)][(int)env->player_pos_x] != '1')
            env->player_pos_y -= move_y;   
    }
}

void    rotate(t_env *env, double cam_speed)
{
    double old_dir_x;
    double old_plane_x;
    
    old_dir_x = env->dir_x;
    old_plane_x = env->plane_x;

    env->dir_x = env->dir_x * cos(cam_speed) - env->dir_y * sin(cam_speed);
    env->dir_y = old_dir_x * sin(cam_speed) + env->dir_y * cos(cam_speed);

    env->plane_x = env->plane_x * cos(cam_speed) - env->plane_y * sin(cam_speed);
    env->plane_y = old_plane_x * sin(cam_speed) + env->plane_y * cos(cam_speed);
}

int	key_hook(int key, t_env *env)
{
	if (key == KEY_ESC)
		close_game(env);
    else if (key == KEY_W)
		move(env, env->dir_x * env->move_speed, env->dir_y * env->move_speed, 1);
    else if (key == KEY_S)
		move(env, env->dir_x * env->move_speed, env->dir_y * env->move_speed, -1);
    else if (key == KEY_D)
		move(env, env->plane_x * env->move_speed, env->plane_y * env->move_speed, 1);
    else if (key == KEY_A)
		move(env, env->plane_x * env->move_speed, env->plane_y * env->move_speed, -1);
    else if (key == KEY_R)
		rotate(env, -env->cam_speed);
    else if (key == KEY_L)
		rotate(env, env->cam_speed);
	return (0);
}