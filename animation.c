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

void	save_path(t_coord current_pos, t_vars *vars)
{
	t_path	*path;

	malloc_protection(path = malloc(sizeof(t_path)), MALLOC_ERROR);
	path->dir = vars->direction;
	path->pos = current_pos;
	if (vars->path == NULL)
	{
		vars->path = ft_lstnew(path);
	}
	else
	{
		ft_lstadd_front(&vars->path, ft_lstnew(path));
	}
	if (ft_lstsize(vars->path) > vars->points + 1)
	{
		lstremove_back(&vars->path);
	}
}

void	place_zombies(t_vars *vars)
{
	t_list		*path;
	t_coord		pos;
	t_direction	dir;

	path = vars->path;
	while (path)
	{
		pos = ((t_path *)path->content)->pos;
		dir = ((t_path *)path->content)->dir;
		if (dir == UP)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.up[vars->step], pos.x, pos.y);
		if (dir == DOWN)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.down[vars->step], pos.x, pos.y);
		if (dir == RIGHT)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.right[vars->step], pos.x, pos.y);
		if (dir == LEFT)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.left[vars->step], pos.x, pos.y);
		path = path->next;
	}
}

void	destroy_char_images(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		mlx_destroy_image(vars->mlx, vars->sprites.player.down[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.player.up[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.player.right[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.player.left[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.zombie.down[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.zombie.up[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.zombie.right[i]);
		mlx_destroy_image(vars->mlx, vars->sprites.zombie.left[i]);
		i++;
	}
}

void	destroy_images(t_vars *vars)
{
	destroy_char_images(vars);
	mlx_destroy_image(vars->mlx, vars->sprites.ui_moves);
	mlx_destroy_image(vars->mlx, vars->sprites.enemy);
	mlx_destroy_image(vars->mlx, vars->sprites.ui_points);
	mlx_destroy_image(vars->mlx, vars->sprites.wall_corner);
	mlx_destroy_image(vars->mlx, vars->sprites.wall_horiz);
	mlx_destroy_image(vars->mlx, vars->sprites.wall_vert);
	mlx_destroy_image(vars->mlx, vars->sprites.tree);
	mlx_destroy_image(vars->mlx, vars->sprites.gate_closed);
	mlx_destroy_image(vars->mlx, vars->sprites.gate_open);
	mlx_destroy_image(vars->mlx, vars->sprites.ground);
	mlx_destroy_image(vars->mlx, vars->sprites.coll);
	mlx_destroy_image(vars->mlx, vars->sprites.start);
	mlx_destroy_image(vars->mlx, vars->img.img);
}
