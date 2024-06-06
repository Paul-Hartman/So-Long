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

void draw_map(t_vars vars)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int distX = vars.screenwidth / vars.leg.col;
    int distY = vars.screenheight / vars.leg.row;
	while(i < vars.leg.row)
	{
		j = 0;
		x = 0;
		while(j < vars.leg.col)
		{
			if(vars.map[i][j] == '1')
				mlx_put_image_to_window(vars.mlx, vars.win, vars.wall_img, x, y);
			else if(vars.map[i][j] == '0')
				mlx_put_image_to_window(vars.mlx, vars.win, vars.floor_img, x, y);
			else if(vars.map[i][j] == 'P')
				mlx_put_image_to_window(vars.mlx, vars.win, vars.start_img, x, y);
			else if(vars.map[i][j] == 'E')
				mlx_put_image_to_window(vars.mlx, vars.win, vars.exit_img, x, y);
			else if(vars.map[i][j] == 'C')
				mlx_put_image_to_window(vars.mlx, vars.win, vars.coll_img, x, y);
			x+=distX;
			j++;
		}
		
		y+=distY;
		i++;
	}



}
void collision(t_vars *vars)
{
	int player_grid_x = vars->x / CHAR_HEIGHT;
	int player_grid_y = vars->y / CHAR_HEIGHT;
	
	
	if(vars->map[player_grid_y][player_grid_x] == 'C')
	{
		
		vars->points++;
		vars->map[player_grid_y][player_grid_x] = '0';
		//printf("points: %i\n", vars->points);
		
	}
	if(vars->map[player_grid_y][player_grid_x] == 'E' && vars->points == vars->leg.c_count)
	{
		printf("You win\n");
		close_window(vars);
		exit(0);
	}
	
}

int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->char_img);
	mlx_destroy_image(vars->mlx, vars->wall_img);
	mlx_destroy_image(vars->mlx, vars->floor_img);
	mlx_destroy_image(vars->mlx, vars->coll_img);
	mlx_destroy_image(vars->mlx, vars->start_img);
	mlx_destroy_image(vars->mlx, vars->exit_img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	
	free_map(vars->map, vars->leg.row);
	free(vars->leg.c);
	free(vars->mlx);
	exit(0);
	return (0);
}


int	move_charachter(int keycode, t_vars *vars)
{
	int new_x = vars->x;
	int new_y = vars->y;
	
	vars->moves++;
	//printf("moves: %i\n", vars->moves);
	
	if(keycode == KEY_ESC)
	{
		close_window(vars);
	}
	if((keycode == KEY_UP || keycode == KEY_W)  && vars->y > 0)
		new_y -=CHAR_HEIGHT;
	if((keycode == KEY_DOWN  || keycode == KEY_S) && vars->y < vars->screenheight)
		new_y +=CHAR_HEIGHT;
	if((keycode == KEY_RIGHT || keycode == KEY_D) && vars->x < vars->screenwidth)
		new_x +=CHAR_HEIGHT;
	if((keycode == KEY_LEFT  || keycode == KEY_A) && vars->x > 0)
		new_x -=CHAR_HEIGHT;

	 int player_grid_x = new_x / CHAR_HEIGHT;
    int player_grid_y = new_y / CHAR_HEIGHT;

    if(vars->map[player_grid_y][player_grid_x] != '1') {
        vars->x = new_x;
        vars->y = new_y;
    }
	//my_mlx_pixel_put(&vars->img, vars->x, vars->y, 0x00FF0000);
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}


int draw_next_frame(t_vars *vars)
{
	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars->win);
	collision(vars);
	draw_map(*vars);
	char *str = ft_itoa(vars->moves);
	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->char_img, vars->x, vars->y);
	mlx_string_put(vars->mlx, vars->win, 20, 20, 0xFF0000, "Moves: ");
	mlx_string_put(vars->mlx, vars->win, 100, 20, 0xFF0000, str);
	free(str);
	
	//mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, vars->win);
    //mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, vars->win);

	return (0);
}

t_vars init()
{
	t_vars vars;
	vars.leg = check_map("map.ber");

	vars.map = read_map("map.ber", &vars);
	
	vars.x = vars.leg.p.x *CHAR_HEIGHT;
	vars.y = vars.leg.p.y * CHAR_HEIGHT;
	vars.moves = 0;
	vars.points = 0;

	vars.color = 0x00000000;
	vars.screenwidth = vars.leg.col*CHAR_HEIGHT;
	vars.screenheight = vars.leg.row*CHAR_HEIGHT;
	vars.mlx = mlx_init();
	if(!vars.mlx)
	{
		printf("mlx init error\n");
		exit(1);
	}
	//printf("width %i\n  height %i", vars.screenwidth, vars.screenheight);
	vars.win = mlx_new_window(vars.mlx, vars.screenwidth, vars.screenheight, "GraveDigger");
	vars.char_img = mlx_xpm_file_to_image(vars.mlx, "char.xpm", &vars.img_width, &vars.img_height);
	vars.wall_img = mlx_xpm_file_to_image(vars.mlx, "wall.xpm", &vars.img_width, &vars.img_height);
	vars.floor_img = mlx_xpm_file_to_image(vars.mlx, "ground.xpm", &vars.img_width, &vars.img_height);
	vars.coll_img = mlx_xpm_file_to_image(vars.mlx, "collect.xpm", &vars.img_width, &vars.img_height);
	vars.start_img = mlx_xpm_file_to_image(vars.mlx, "start.xpm", &vars.img_width, &vars.img_height);
	vars.exit_img = mlx_xpm_file_to_image(vars.mlx, "exit.xpm", &vars.img_width, &vars.img_height);
	
	vars.img.img = mlx_new_image(vars.mlx, vars.screenwidth, vars.screenheight);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
	  							&vars.img.endian);
	return (vars);
}