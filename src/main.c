/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/09 15:19:48 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_management(t_env *env)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (env->img[i].mlx_img)
			mlx_destroy_image(env->mlx, env->img[i].mlx_img);
		if (i != 0 && env->img[i].path)
			free(env->img[i].path);
	}
	if (env->minimap.mlx_img)
		mlx_destroy_image(env->mlx, env->minimap.mlx_img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	free(env->mlx);
	if (env->map)
		ft_freetab(env->map);
	exit(0);
}

int	error_management(t_env *env, char *msg)
{
	int	i;

	i = -1;
	if (msg)
		ft_putstr_fd(msg, 2);
	while (++i < 5)
	{
		if (env->img[i].mlx_img)
			mlx_destroy_image(env->mlx, env->img[i].mlx_img);
		if (i != 0 && env->img[i].path)
			free(env->img[i].path);
	}
	if (env->minimap.mlx_img)
		mlx_destroy_image(env->mlx, env->minimap.mlx_img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	free(env->mlx);
	if (env->map)
		ft_freetab(env->map);
	exit(1);
}

void	ft_init_game(t_env *env)
{
	env->move_speed = 0.09;
	env->cam_speed = 0.09;
	env->mlx = mlx_init();
	if (!env->mlx)
		error_management(env, "Error\nInitialisation of display has failed\n");
	env->mlx_win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "cub3d");
	if (!env->mlx_win)
		error_management(env, "Error\nInitialisation of window has failed\n");
	env->minimap.mlx_img = mlx_new_image(env->mlx, WIDTH / 7, HEIGHT / 7);
	env->minimap.addr = mlx_get_data_addr(env->minimap.mlx_img,
			&env->minimap.bpp, &env->minimap.line_len, &env->minimap.endian);
}

void	launch_game(t_env *env)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i == 0)
			env->img[i].mlx_img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
		else
		{
			env->img[i].mlx_img = mlx_xpm_file_to_image(env->mlx,
					env->img[i].path, &env->img[i].width, &env->img[i].height);
		}
		if (!env->img[i].mlx_img || !env->minimap.mlx_img)
			error_management(env, "Error\nimage creation failed\n");
		env->img[i].addr = mlx_get_data_addr(env->img[i].mlx_img,
				&env->img[i].bpp, &env->img[i].line_len, &env->img[i].endian);
		i++;
	}
	mlx_loop_hook(env->mlx, &render, env);
	mlx_hook(env->mlx_win, 2, 1L << 0, key_hook, env);
	mlx_hook(env->mlx_win, 6, 1L << 6, mouse_hook, env);
	mlx_hook(env->mlx_win, 17, 1L << 0, close_management, env);
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
