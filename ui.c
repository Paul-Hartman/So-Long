/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:02:12 by phartman          #+#    #+#             */
/*   Updated: 2024/06/12 19:42:25 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void draw_ui(t_vars *vars)
{
	char	*str;

	mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.UI_moves, 0, vars->screenheight);
	mlx_put_image_to_window(vars->mlx, vars->win,
			vars->sprites.UI_points, vars->screenwidth - 128, vars->screenheight);
	
	str = ft_itoa(vars->moves);
	mlx_string_put(vars->mlx, vars->win, 40, vars->screenheight + 53, 0xFF0000, "Moves: ");
	mlx_string_put(vars->mlx, vars->win, 75, vars->screenheight + 54, 0xFF0000, str);
	free(str);
}