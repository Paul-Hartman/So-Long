/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:01:30 by phartman          #+#    #+#             */
/*   Updated: 2024/06/13 16:29:35 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_coord	pick_enemy_spaces(t_vars *vars, int direction)
{
	t_coord	coord;

	if (direction == 1)
	{
		coord.x = 0;
		coord.y = 0;
		while (vars->map[coord.y][coord.x] != '0' && coord.x <= vars->leg.col
			- 1 && coord.y <= vars->leg.row - 1)
		{
			coord.x++;
			coord.y++;
		}
	}
	else
	{
		coord.x = vars->leg.col - 1;
		coord.y = vars->leg.row - 1;
		while (vars->map[coord.y][coord.x] != '0' && coord.x >= 0
			&& coord.y >= 0)
		{
			coord.x--;
			coord.y--;
		}
	}
	return (coord);
}

int	enemy_init(t_vars *vars)
{
	t_enemy	enemy;

	enemy.point_a = pick_enemy_spaces(vars, 0);
	enemy.point_b = pick_enemy_spaces(vars, 1);
	enemy.pos = enemy.point_a;
	enemy.target = enemy.point_b;
	enemy.x = enemy.pos.x * CHAR_HEIGHT;
	enemy.y = enemy.pos.y * CHAR_HEIGHT;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.enemy, enemy.x,
		enemy.y);
	vars->enemy = enemy;
	return (0);
}

void	switch_targets(t_enemy *enemy)
{
	if (enemy->target.x == enemy->point_a.x
		&& enemy->target.y == enemy->point_a.y)
		enemy->target = enemy->point_b;
	else
		enemy->target = enemy->point_a;
}

void	update_enemy(t_enemy *enemy, t_vars *vars)
{
	if (enemy->pos.x == enemy->target.x && enemy->pos.y == enemy->target.y)
		switch_targets(enemy);
	else if (enemy->pos.x != enemy->target.x)
	{
		if (enemy->pos.x > enemy->target.x)
			move_enemy(enemy, vars, -1, 0);
		else
			move_enemy(enemy, vars, 1, 0);
	}
	else if (enemy->pos.y != enemy->target.y)
	{
		if (enemy->pos.y > enemy->target.y)
			move_enemy(enemy, vars, 0, -1);
		else
			move_enemy(enemy, vars, 0, 1);
	}
}

void	move_enemy(t_enemy *enemy, t_vars *vars, int new_x, int new_y)
{
	int	grid_x;
	int	grid_y;

	grid_x = new_x + enemy->pos.x;
	grid_y = new_y + enemy->pos.y;
	if (grid_x >= 0 && grid_x < vars->leg.col && grid_y >= 0
		&& grid_y < vars->leg.row && vars->map[grid_y][grid_x] != '1')
	{
		enemy->x = grid_x * CHAR_HEIGHT;
		enemy->y = grid_y * CHAR_HEIGHT;
		enemy->pos = assign_coord(grid_x, grid_y);
	}
	else
	{
		if (!new_x && vars->map[grid_y][grid_x + new_y] == '0')
			move_enemy(enemy, vars, new_y, 0);
		else if (!new_y && vars->map[grid_y + new_x][grid_x] == '0')
			move_enemy(enemy, vars, 0, new_x);
		else if (!new_y && vars->map[grid_y + -new_x][grid_x] == '0')
			move_enemy(enemy, vars, 0, -new_x);
		else if (!new_x && vars->map[grid_y][grid_x + -new_y] == '0')
			move_enemy(enemy, vars, -new_y, 0);
		else
			switch_targets(enemy);
	}
}
