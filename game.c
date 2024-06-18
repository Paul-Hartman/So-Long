/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:10:45 by phartman          #+#    #+#             */
/*   Updated: 2024/06/18 19:50:22 by phartman         ###   ########.fr       */
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
		ft_printf("You win\n");
		close_window(vars);
		exit(0);
	}
	if (player_grid_x == vars->enemy.pos.x
		&& player_grid_y == vars->enemy.pos.y)
	{
		ft_printf("You lose\n");
		close_window(vars);
		exit(0);
	}
}

int	close_window(t_vars *vars)
{
	destroy_images(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free_map(vars->map, vars->leg.row);
	ft_lstclear(&vars->path, free);
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

	player_grid_x = new_x / CHAR_HEIGHT;
	player_grid_y = new_y / CHAR_HEIGHT;
	if (vars->map[player_grid_y][player_grid_x] != '1')
	{
		if (new_x > vars->x)
			vars->direction = RIGHT;
		if (new_x < vars->x)
			vars->direction = LEFT;
		if (new_y < vars->y)
			vars->direction = UP;
		if (new_y > vars->y)
			vars->direction = DOWN;
		vars->x = new_x;
		vars->y = new_y;
		vars->moves++;
		vars->step = 1 - vars->step;
		save_path(assign_coord(new_x, new_y), vars);
		ft_printf("moves: %d\n", vars->moves);
		draw_next_frame(vars);
		return (1);
	}
	return (0);
}
