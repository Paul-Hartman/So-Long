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
	t_path		strt;
	strt.pos = vars.leg.p;
	strt.dir = DOWN;
	vars.path = ft_lstnew(&strt);
	vars.step = 0;
	vars.direction = DOWN;
	vars.moves = 0;
	vars.points = 0;
	vars.screenwidth = vars.leg.col * CHAR_HEIGHT;
	vars.screenheight = vars.leg.row * CHAR_HEIGHT;
	vars.mlx = mlx_init();
	if (!vars.mlx)
		print_error(MLX_INIT_ERROR);
	vars.win = mlx_new_window(vars.mlx, vars.screenwidth,
			vars.screenheight + (CHAR_HEIGHT * 2), "so_long");
	if (!vars.win)
		print_error(MLX_WINDOW_ERROR);
	save_images(&vars);
	enemy_init(&vars);
	vars.img.img = mlx_new_image(vars.mlx, vars.screenwidth, vars.screenheight);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	return (vars);
}

void	save_images(t_vars *vars)
{
	t_sprites		sprite;
	int				width;
	int				height;

	sprite.player = save_char_sprites(vars);
	sprite.zombie = save_zomb_sprites(vars);
	sprite.wall = mlx_xpm_file_to_image(vars->mlx,
			"./textures/wall.xpm", &width, &height);
	sprite.ground = mlx_xpm_file_to_image(vars->mlx,
			"./textures/ground.xpm", &width, &height);
	sprite.coll = mlx_xpm_file_to_image(vars->mlx,
			"./textures/collect.xpm", &width, &height);
	sprite.start = mlx_xpm_file_to_image(vars->mlx,
			"./textures/start.xpm", &width, &height);
	sprite.exit = mlx_xpm_file_to_image(vars->mlx,
			"./textures/door_closed.xpm", &width, &height);
	sprite.UI_points = mlx_xpm_file_to_image(vars->mlx,
			"./textures/points_UI.xpm", &width, &height);
	sprite.UI_moves = mlx_xpm_file_to_image(vars->mlx,
			"./textures/moves_UI.xpm", &width, &height);
	sprite.enemy = mlx_xpm_file_to_image(vars->mlx,
			"./textures/enemy.xpm", &width, &height);
	vars->sprites = sprite;
}

int	draw_next_frame(t_vars *vars)
{

	
	draw_map(*vars);
	draw_ui(vars);
	
	collision(vars);
	place_zombies(vars);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->sprites.enemy, vars->enemy.x, vars->enemy.y);
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

void	place_sprite(t_vars vars, char sym, int x, int y)
{
	if (sym == '1')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.wall, x, y);
	else if (sym == '0')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.ground, x, y);
	else if (sym == 'P')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.start, x, y);
	else if (sym == 'E')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.exit, x, y);
	else if (sym == 'C')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.sprites.coll, x, y);
}
