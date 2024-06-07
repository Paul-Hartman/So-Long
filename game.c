/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:10:45 by phartman          #+#    #+#             */
/*   Updated: 2024/06/06 18:17:09 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "game.h"

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




void	collision(t_vars *vars)
{
	int	player_grid_x;
	int	player_grid_y;

	player_grid_x = vars->x / CHAR_HEIGHT;
	player_grid_y = vars->y / CHAR_HEIGHT;
	if (vars->map[player_grid_y][player_grid_x] == 'C')
	{
		vars->points++;
		vars->map[player_grid_y][player_grid_x] = '0';

	}
	if (vars->map[player_grid_y][player_grid_x] == 'E'
		&& vars->points == vars->leg.c_count)
	{
		printf("You win\n");
		close_window(vars);
		exit(0);
	}
}

int	close_window(t_vars *vars)
{

	mlx_destroy_image(vars->mlx, vars->sprites.player);
	mlx_destroy_image(vars->mlx, vars->sprites.wall);
	mlx_destroy_image(vars->mlx, vars->sprites.ground);
	mlx_destroy_image(vars->mlx, vars->sprites.coll);
	mlx_destroy_image(vars->mlx, vars->sprites.start);
	mlx_destroy_image(vars->mlx, vars->sprites.exit);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free_map(vars->map, vars->leg.row);
	free(vars->leg.c);
	free(vars->mlx);
	exit(0);
	return (0);
}

int	process_key_stroke(int keycode, t_vars *vars)
{
	int	new_x;
	int	new_y;

	new_y = vars->y;
	new_x = vars->x;
	if (keycode == KEY_ESC)
		close_window(vars);
	if ((keycode == KEY_UP || keycode == KEY_W))
		new_y -= CHAR_HEIGHT;
	if ((keycode == KEY_DOWN || keycode == KEY_S))
		new_y += CHAR_HEIGHT;
	if ((keycode == KEY_RIGHT || keycode == KEY_D))
		new_x += CHAR_HEIGHT;
	if ((keycode == KEY_LEFT || keycode == KEY_A))
		new_x -= CHAR_HEIGHT;
	move_charachter(new_x, new_y, vars);
	return (0);
}


int	move_charachter(int new_x, int new_y, t_vars *vars)
{
	int	player_grid_x;
	int	player_grid_y;

	vars->moves++;
	player_grid_x = new_x / CHAR_HEIGHT;
	player_grid_y = new_y / CHAR_HEIGHT;
	if (vars->map[player_grid_y][player_grid_x] != '1')
	{
		vars->x = new_x;
		vars->y = new_y;
	}
	return (0);
}


int	draw_next_frame(t_vars *vars)
{
	char	*str;

	str = ft_itoa(vars->moves);
	collision(vars);
	draw_map(*vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.player,
		vars->x, vars->y);
	mlx_string_put(vars->mlx, vars->win, 20, 20, 0xFF0000, "Moves: ");
	mlx_string_put(vars->mlx, vars->win, 100, 20, 0xFF0000, str);
	free(str);
	return (0);
}

void print_error(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

void 	save_images(t_vars *vars)
{
	t_sprites		sprite;
	int				width;
	int				height;

	sprite.player = mlx_xpm_file_to_image(vars->mlx,
			"./sprites/char.xpm", &width, &width);
	sprite.wall = mlx_xpm_file_to_image(vars->mlx,
			"./sprites/wall.xpm", &width, &height);
	sprite.ground = mlx_xpm_file_to_image(vars->mlx,
			"./sprites/ground.xpm", &width, &height);
	sprite.coll = mlx_xpm_file_to_image(vars->mlx,
			"./sprites/collect.xpm", &width, &height);
	sprite.start = mlx_xpm_file_to_image(vars->mlx,
			"./sprites/start.xpm", &width, &height);
	sprite.exit = mlx_xpm_file_to_image(vars->mlx,
			"./sprites/exit.xpm", &width, &height);
	vars->sprites = sprite;
	if (vars->sprites.player == NULL || vars->sprites.wall == NULL
		|| vars->sprites.ground == NULL || vars->sprites.coll == NULL
		|| vars->sprites.start == NULL || vars->sprites.exit == NULL)
		print_error(XPM_ERROR);
}



t_vars init(char *file)
{
	t_vars	vars;

	vars.leg = check_map(file);
	vars.map = read_map(file, &vars);
	vars.x = vars.leg.p.x * CHAR_HEIGHT;
	vars.y = vars.leg.p.y * CHAR_HEIGHT;
	vars.moves = 0;
	vars.points = 0;
	vars.screenwidth = vars.leg.col * CHAR_HEIGHT;
	vars.screenheight = vars.leg.row * CHAR_HEIGHT;
	vars.mlx = mlx_init();
	if (!vars.mlx)
		print_error(MLX_INIT_ERROR);
	vars.win = mlx_new_window(vars.mlx, vars.screenwidth,
			vars.screenheight, "so_long");
	if (!vars.win)
		print_error(MLX_WINDOW_ERROR);
	save_images(&vars);
	vars.img.img = mlx_new_image(vars.mlx, vars.screenwidth, vars.screenheight);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);
	return (vars);
}
