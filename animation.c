/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:45:29 by phartman          #+#    #+#             */
/*   Updated: 2024/06/13 15:38:21 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_player	save_char_sprites(t_vars *vars)
{
	t_player		player;
	int				width;
	int				height;

	player.down[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_dn1.xpm", &width, &height);
	player.down[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_dn2.xpm", &width, &height);
	player.up[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_up1.xpm", &width, &height);
	player.up[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_up2.xpm", &width, &height);
	player.left[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_lf1.xpm", &width, &height);
	player.left[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_lf2.xpm", &width, &height);
	player.right[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_rt1.xpm", &width, &height);
	player.right[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/pl_rt2.xpm", &width, &height);
	return (player);
}

void	xpm_check(t_sprites sprites)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (!sprites.player.down[i] || !sprites.player.up[i]
			|| !sprites.player.left[i] || !sprites.player.right[i]
			||!sprites.wall || !sprites.ground || !sprites.coll
			|| !sprites.start || !sprites.exit)
			print_error(XPM_ERROR);
		i++;
	}
}

void	destroy_images(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		mlx_destroy_image(vars->mlx, vars->sprites.player.down[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.player.up[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.player.right[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.player.left[i]);
		i++;
	}
	mlx_destroy_image(vars->mlx, vars->sprites.UI_moves);
	mlx_destroy_image(vars->mlx, vars->sprites.UI_points);
	mlx_destroy_image(vars->mlx, vars->sprites.wall);
	mlx_destroy_image(vars->mlx, vars->sprites.ground);
	mlx_destroy_image(vars->mlx, vars->sprites.coll);
	mlx_destroy_image(vars->mlx, vars->sprites.start);
	mlx_destroy_image(vars->mlx, vars->sprites.exit);
	mlx_destroy_image(vars->mlx, vars->img.img);
}

void	player_anim(t_vars *vars)
{
	if (vars->direction == UP)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.player.up[vars->step], vars->x, vars->y);
	if (vars->direction == DOWN)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.player.down[vars->step], vars->x, vars->y);
	if (vars->direction == RIGHT)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.player.right[vars->step], vars->x, vars->y);
	if (vars->direction == LEFT)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.player.left[vars->step], vars->x, vars->y);
}
