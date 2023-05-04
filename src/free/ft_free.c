/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/03 19:17:26 by adcarnec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "utils.h"
//#include "mlx.h"

void	ft_free(t_env *env)
{
/* 	if (env->win)
		mlx_clear_window(env->mlx, env->win);
	if (env->wall_n_img)
		mlx_destroy_image(env->mlx, env->wall_n_img);
	if (env->wall_s_img)
		mlx_destroy_image(env->mlx, env->wall_s_img);
	if (env->wall_w_img)
		mlx_destroy_image(env->mlx, env->wall_w_img);
	if (env->wall_e_img)
		mlx_destroy_image(env->mlx, env->wall_e_img);
	if (env->mlx)
		mlx_destroy_display(env->mlx); */
	if (env->mlx)
		free(env->mlx);
	if (env->map)
		ft_freetab(env->map);
	if (env)
		free(env);
}
