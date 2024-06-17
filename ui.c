/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:02:12 by phartman          #+#    #+#             */
/*   Updated: 2024/06/13 15:37:49 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_ui(t_vars *vars)
{
	char	*moves_str;
	char	*points_str;
	char	*goal_str;
	int		y;

	y = vars->screenheight + 53;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.ui_moves, 0,
		vars->screenheight);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.ui_points,
		vars->screenwidth - 128, vars->screenheight);
	moves_str = ft_itoa(vars->moves);
	points_str = ft_itoa(vars->points);
	goal_str = ft_itoa(vars->leg.c_count);
	draw_string(vars, "Moves:", 40, y);
	draw_string(vars, moves_str, 75, y);
	draw_string(vars, "Pts:", vars->screenwidth - 115, y);
	draw_string(vars, points_str, vars->screenwidth - 85, y);
	draw_string(vars, "/", vars->screenwidth - 75, y);
	draw_string(vars, goal_str, vars->screenwidth - 65, y);
	draw_progress_bars(vars);
	free(moves_str);
	free(points_str);
	free(goal_str);
}

void	draw_string(t_vars *vars, char *str, int x, int y)
{
	mlx_string_put(vars->mlx, vars->win, x, y, 0xFF0000, str);
}

void	draw_progress_bars(t_vars *vars)
{
	int		moves_bar_width;
	int		points_bar_width;
	t_coord	start;

	moves_bar_width = (int)((float)vars->moves / MAX_MOVES * MOVES_BAR_WIDTH);
	points_bar_width = (int)((float)vars->points / vars->leg.c_count
			* POINTS_BAR_WIDTH);
	start = assign_coord(22, vars->screenheight + 28);
	draw_bar(vars, moves_bar_width, MOVES_BAR_HEIGHT, start);
	start = assign_coord(vars->screenwidth - 117, vars->screenheight + 14);
	draw_bar(vars, points_bar_width, POINTS_BAR_HEIGHT, start);
}

void	draw_bar(t_vars *vars, int width, int height, t_coord start)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			mlx_pixel_put(vars->mlx, vars->win, start.x + x, start.y + y,
				0xFF0000);
			y++;
		}
		x++;
	}
}
