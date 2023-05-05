/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/05 15:53:13 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_game(t_env *env)
{
	int	i;

	i = -1;
	while (++i < 5)
		mlx_destroy_image(env->mlx, env->img[i].mlx_img);
	mlx_destroy_window(env->mlx, env->mlx_win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	if (env->map)
		ft_freetab(env->map);
	exit(0);
}

void	graphic_error(t_env *env, char *message)
{
	int	i;

	i = 0;
	ft_putstr_fd(message, 2);
	mlx_destroy_image(env->mlx, env->img[0].mlx_img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit(EXIT_FAILURE);
}

void	ft_init_game(t_env *env)
{
	env->move_speed = 0.09;
	env->cam_speed = 0.09;
	env->img[1].path = "img/WALL.xpm";
	env->img[2].path = "img/MARBFAC2.xpm";
	env->img[3].path = "img/STONE3.xpm";
	env->img[4].path = "img/SP_HOT1.xpm";
	env->mlx = mlx_init();
	if (!env->mlx)
		graphic_error(env, "Error : Initialisation of display has failed\n");
	env->mlx_win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "cub3d");
	if (!env->mlx_win)
		graphic_error(env, "Error : Initialisation of window has failed\n");
}

void	launch_game(t_env *env)
{
	int	i;

	env->img[0].mlx_img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->img[0].addr = mlx_get_data_addr(env->img[0].mlx_img, &env->img[0].bpp,
			&env->img[0].line_len, &env->img[0].endian);
	i = 1;
	while (i < 5)
	{
		env->img[i].mlx_img = mlx_xpm_file_to_image(env->mlx, env->img[i].path,
				&env->img[i].width, &env->img[i].height);
		if (!env->img[i].mlx_img)
			graphic_error(env, "Error : Path texture is incorrect\n");
		env->img[i].addr = mlx_get_data_addr(env->img[i].mlx_img,
				&env->img[i].bpp, &env->img[i].line_len, &env->img[i].endian);
		i++;
	}
	mlx_loop_hook(env->mlx, &render, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, key_hook, env);
	mlx_hook(env->mlx_win, 17, 1L << 0, close_game, env);
	mlx_loop(env->mlx);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (ft_init(&env, ac, av) == -1)
		return (ft_free(&env), -1);
	ft_init_game(&env);
	launch_game(&env);
	ft_free(&env);
	return (0);
}
