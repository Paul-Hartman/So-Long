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





