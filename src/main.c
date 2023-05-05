/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/05 09:28:47 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void launch_game(t_env *env)
{
	env->move_speed = 0.09;
	env->cam_speed = 0.09;
	env->mlx = mlx_init();
    if (!env->mlx)
		graphic_error(env, "Error\nInitialisation of display has failed\n");
    env->mlx_win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "cub3d");
    if (!env->mlx_win)
		graphic_error(env, "Error\nInitialisation of window has failed\n");
    env->img.mlx_img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    env->img.addr = mlx_get_data_addr(env->img.mlx_img, &env->img.bpp,
    &env->img.line_len, &env->img.endian);
    mlx_loop_hook(env->mlx, &render, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, key_hook, env);
    mlx_hook(env->mlx_win, 17, 1L << 0, close_game, env);
	mlx_loop(env->mlx);
}

int	main(int ac, char **av)
{
	t_env		env;

	if (ft_init(&env, ac, av) == -1)
		return (ft_free(&env), -1);
	launch_game(&env);
	ft_free(&env); 
	return (0);
}
