/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:17:23 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/04 17:35:06 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "utils.h"
//#include "mlx.h"

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
void	ft_free(t_env *env)
{
	if (env){
		if (env->mlx)
			free(env->mlx);
		if (env->map)
			ft_freetab(env->map);
	}
}
