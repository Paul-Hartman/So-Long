/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:00 by phartman          #+#    #+#             */
/*   Updated: 2024/06/13 16:09:03 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_vars	init(char *file)
{
	t_vars	vars;

	vars.leg = check_map(file);
	vars.map = read_map(file, &vars);
	vars.x = vars.leg.p.x * CHAR_HEIGHT;
	vars.y = vars.leg.p.y * CHAR_HEIGHT;
	vars.direction = DOWN;
	vars.path = NULL;
	save_path(vars.leg.p, &vars);
	vars.step = 0;
	vars.moves = 0;
	vars.points = 0;
	vars.screenwidth = vars.leg.col * CHAR_HEIGHT;
	vars.screenheight = vars.leg.row * CHAR_HEIGHT;
	vars.mlx = mlx_init();
	malloc_protection(vars.mlx, MLX_INIT_ERROR);
	vars.win = mlx_new_window(vars.mlx, vars.screenwidth, vars.screenheight
			+ (CHAR_HEIGHT * 2), "so_long");
	malloc_protection(vars.win, MLX_WINDOW_ERROR);
	save_images(&vars);
	enemy_init(&vars);
	vars.img.img = mlx_new_image(vars.mlx, vars.screenwidth, vars.screenheight);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	return (vars);
}

int	draw_next_frame(t_vars *vars)
{
	draw_map(*vars);
	draw_ui(vars);
	collision(vars);
	if (vars->points > 0)
		place_zombies(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.enemy,
		vars->enemy.x, vars->enemy.y);
	player_anim(vars);
	return (0);
}

void	draw_map(t_vars vars)
{
	int	i;
	int	j;
	int	x;
	int	y;

	y = 0;
	i = 0;
	while (i < vars.leg.row)
	{
		j = 0;
		x = 0;
		while (j < vars.leg.col)
		{
			place_sprite(vars, vars.map[i][j], x, y);
			x += vars.screenwidth / vars.leg.col;
			j++;
		}
		y += vars.screenheight / vars.leg.row;
		i++;
	}
}

void	place_obstacle(t_vars vars, int x, int y)
{
	int	i;
	int	j;

	i = y / CHAR_HEIGHT;
	j = x / CHAR_HEIGHT;
	if ((i == 0 && j == 0) || (i == 0 && j == vars.leg.col - 1)
		|| (i == vars.leg.row - 1 && j == 0) || (i == vars.leg.row - 1
			&& j == vars.leg.col - 1))
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.wall_corner, x,
			y);
	else if (i == 0 || i == vars.leg.row - 1)
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.wall_horiz, x,
			y);
	else if (j == 0 || j == vars.leg.col - 1)
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.wall_vert, x,
			y);
	else
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.tree, x, y);
}

void	place_sprite(t_vars vars, char sym, int x, int y)
{
	if (sym == '1')
		place_obstacle(vars, x, y);
	else if (sym == '0')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.ground, x, y);
	else if (sym == 'P')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.start, x, y);
	else if (sym == 'E')
	{
		if (vars.points == vars.leg.c_count)
			mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.gate_open,
				x, y);
		else
			mlx_put_image_to_window(vars.mlx, vars.win,
				vars.sprites.gate_closed, x, y);
	}
	else if (sym == 'C')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.coll, x, y);
}
