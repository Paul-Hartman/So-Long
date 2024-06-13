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

t_enemy enem_init()
{
	t_enemy enemy;
	//vars.sprites.enemy = mlx_xpm_file_to_image(vars->mlx,
	//		"./textures/enemy.xpm", &width, &height);
	
	//if(somethig bout free space on map)
	enemy.pointA = assign_coord(0, 0);
	enemy.pointB = assign_coord(0, 10);
	enemy.pos = enemy.pointA;
	enemy.target = &enemy.pointB;
}

t_coord	compare_coords(t_coord a, t_coord b)
{
	t_coord diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	return (diff);
}

void updateEnemy(t_enemy *enemy, t_vars *vars)
{
	t_coord diff;
	
	diff = compare_coords(enemy->pos, *enemy->target);
	if(diff.x != 0 && diff.y != 0)
	{
		if(diff.x > 0)
			moveEnemy(enemy, -1, 0, vars);
		else
			moveEnemy(enemy, 1, 0, vars);
		if(diff.y > 0)
			moveEnemy(enemy, 0, -1, vars);
		else
			moveEnemy(enemy, 0, 1, vars);
	}
	else
	{
		if(enemy->target == &enemy->pointA)
			enemy->target = &enemy->pointB;
		else
			enemy->target = &enemy->pointA;
	}
}

void moveEnemy(t_enemy *enemy, t_vars *vars, int new_x, int new_y)
{
	int	grid_x;
	int	grid_y;

	grid_x = new_x / CHAR_HEIGHT;
	grid_y = new_y / CHAR_HEIGHT;
	if (vars->map[grid_y][grid_x] != '1')
	{
		enemy->x = new_x;
		enemy->y = new_y;
	}
	mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.enemy, enemy->x, enemy->y);
}