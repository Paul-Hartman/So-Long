/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:28:37 by phartman          #+#    #+#             */
/*   Updated: 2024/06/18 19:45:30 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
		print_error(AGUMENT_ERROR);
	vars = init(argv[1]);
	draw_next_frame(&vars);
	mlx_hook(vars.win, 2, 1L << 0, process_key_stroke, &vars);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
