/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:28 by phartman          #+#    #+#             */
/*   Updated: 2024/06/05 16:13:25 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"



t_legend check_map(char *filename)
{
	int fd;
	t_legend leg;
	char buf;
	int p_count;
	int e_count;
	int obst_count;
	p_count = 0;
	leg.c_count = 0;
	e_count = 0;
	obst_count = 0;
	if (!filename || !ft_strnstr(filename, ".ber", ft_strlen(filename)))
	{
		printf("wrong file Error\n");
		exit (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("read Error\n");
		exit (0);
	}
	leg.col = 0;
	leg.row = 1;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
		{
			leg.col = 0;
			leg.row++;
		}
		else if (buf == '0' || buf == '1' || buf == 'C' || buf == 'E' || buf == 'P')
		{
			leg.col++;
			if (buf == 'P')
				p_count++;
			if (buf == 'E')
				e_count++;
			if (buf == 'C')
				leg.c_count++;
			if(buf == '1')
				obst_count++;
		}
		else
		{
			printf("map error Error\n");
			exit (0);
		}
	}
	if(p_count != 1 || e_count != 1 || leg.c_count < 1 || obst_count < 2*((leg.col -1) + (leg.row -1)))
	{
		
		printf("map error Error\n");
		exit (0);
	}
	printf("leg.col: %d\n", leg.col);
		printf("leg.row: %d\n", leg.row);
		printf("p_count: %d\n", p_count);
		printf("e_count: %d\n", e_count);
		printf("c_count: %d\n", leg.c_count);
		printf("expeced obst_count: %d\n", 2*((leg.col -1) + (leg.row -1)));	
		printf("obst_count: %d\n", obst_count);
	close(fd);
	return (leg);
}

void lstremove_back(t_list **lst)
{
	if (!lst || !*lst)
		return;
	t_list *current = *lst;
	t_list *previous = NULL;
	while (current->next)
	{
		previous = current;
		current = current->next;
	}
	if (previous)
		previous->next = NULL;
	else
		*lst = NULL;
	free(current);
}

int find_closest_collectable(char **map, t_coord current_pos, t_legend leg, int *collected)
{
	int i;
	int shortest_dist;
	int dist;
	int closest_collectable;
	shortest_dist = INT_MAX;
	i = 0;
	while(i < leg.c_count)
	{
		if(current_pos.x == leg.c[i].x && current_pos.y == leg.c[i].y)
			(*collected)++;
		if (map[leg.c[i].y][leg.c[i].x] != 'T')
		{
			dist = abs(current_pos.x - leg.c[i].x) + abs(current_pos.y - leg.c[i].y);
			if(dist < shortest_dist)
			{
				shortest_dist = dist;
				closest_collectable = i;
			}
		}
		i++;
	}
	
	return (closest_collectable);

}


t_coord get_neighbors(char **map, t_coord current_pos, t_legend leg)
{
	int i;
	
	t_coord directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	t_coord next_pos;
	t_coord chosen_pos;
	static int collected;
	
	next_pos.x = 0;
	next_pos.y = 0;
	chosen_pos.x = -1;
	chosen_pos.y = -1;
	int shortest_dist;
	int neighbor_dist;
	shortest_dist = INT_MAX;
	int j;
	i=0;
	if(collected < leg.c_count)
		j = find_closest_collectable(map, current_pos, leg, &collected);
	while(i < 4)
	{
		next_pos.x = current_pos.x + directions[i].x;
		next_pos.y = current_pos.y + directions[i].y;
		if(next_pos.x < 0 || next_pos.x >= leg.col || next_pos.y < 0 || next_pos.y >= leg.row)
		{
			i++;
			continue;
		}
		if(map[next_pos.y][next_pos.x] == 'F' || map[next_pos.y][next_pos.x] == 'E')
		{
			if(collected == leg.c_count)
			{
				neighbor_dist = abs(next_pos.x - leg.e.x) + abs(next_pos.y - leg.e.y);
			}
			else
			{
				neighbor_dist = abs(next_pos.x - leg.c[j].x) + abs(next_pos.y - leg.c[j].y);
			}
			
			if(neighbor_dist < shortest_dist)
			{
				shortest_dist = neighbor_dist;
				chosen_pos = next_pos;
			}
		}
		i++;
	}
	return (chosen_pos);
}


int greedy_best_search(char **map, t_legend leg)
{
	//unsigned int dist = abs(leg.p.x - leg.e.x) + abs(leg.p.y - leg.e.y);
	t_coord current_pos;
	int steps;
	steps=0;
	current_pos = leg.p;
	map[current_pos.y][current_pos.x] = 'T';
	t_list *queue = ft_lstnew(&leg.p);
	while(queue)
	{
		current_pos = get_neighbors(map, current_pos, leg);
		if(current_pos.x == -1 && current_pos.y == -1 && queue)
		{
			current_pos = *(t_coord *)ft_lstlast(queue)->content;
			lstremove_back(&queue);
			steps--;
		}
		else if(map[current_pos.y][current_pos.x] == 'E')
		{
			printf("number of steps %i\n", steps);
			return (steps);
		}
		else
		{
			map[current_pos.y][current_pos.x] = 'T';
			ft_lstadd_back(&queue, ft_lstnew(&current_pos));
		}
		steps++;
	}
	return (0);
}

int map_isvalidpath(char **map, t_legend leg)
{
	int i;
	i = 0;
	char **path_map;
	path_map = malloc(sizeof(char *) * leg.row);
	while(i < leg.row)
	{
		path_map[i] = malloc(sizeof(char) * leg.col);
		i++;
	}
	i = 0;
	while(i < leg.row)
	{
		int j = 0;
		while(j < leg.col)
		{
			if(map[i][j] == '1')
				path_map[i][j] = 'N';
			else if(map[i][j] == 'E')
				path_map[i][j] = 'E';
			else
				path_map[i][j] = 'F';
			j++;
		}
		i++;
	}
	
	// if (leg.rows < 1 || !map || !map[0]) {
    //     return 0; // Invalid input
    // }
	
	while(i < leg.col)
	{
		if(map[0][i] != '1' || map[leg.row - 1][i] != '1')
			return (0);
		if(i < leg.row)
		{
			if(map[i][0] != '1' || map[i][leg.col - 1] != '1')
			return (0);
		}
		i++;
	}

	
	return (greedy_best_search(path_map, leg));
		
	
}



char **read_map(char *filename, t_legend leg)
{
	int fd;
	char **map;
	char buf;
	int row;
	int col;
	int i;
	i=0;
	
	row = 0;
	col = 0;
	map = malloc(sizeof(char *) * leg.row);
	while(row < leg.row)
	{
		map[row] = malloc(sizeof(char) * leg.col);
		row++;
	}
	leg.c = malloc(sizeof(t_coord) * leg.c_count);
	row = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	
	while (read(fd, &buf, 1) > 0)
	{
		if(buf == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			if(buf == 'P')
			{
				leg.p.x = col;
				leg.p.y = row;
			}
			if(buf == 'E')
			{
				leg.e.x = col;
				leg.e.y = row;
			}
			if(buf == 'C')
			{
				leg.c[i].x = col;
				leg.c[i].y = row;
				i++;
			}
			map[row][col] = buf;
			col++;
		}
	}
	close(fd);
	if(map_isvalidpath(map, leg) == 0)
	{
		printf("map valid Error\n");
		exit (0);
	}
	printf("map is valid\n");
	
	return (map);
}





// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int draw_map(t_vars vars)
// {
// 	int i = 0;
// 	int j = 0;
// 	int x = 0;
// 	int y = 0;
// 	int distX = SCREENWIDTH / vars.leg.col;
//     int distY = SCREENHEIGHT / vars.leg.row;
// 	while(i < vars.leg.row)
// 	{
// 		j = 0;
// 		x = 0;
// 		while(j < vars.leg.col)
// 		{
// 			if(vars.map[i][j] == '1')
// 				mlx_put_image_to_window(vars.mlx, vars.win, vars.wall_img, x, y);
// 			else if(vars.map[i][j] == 'P')
// 				mlx_put_image_to_window(vars.mlx, vars.win, vars.wall_img, x, y);
// 			else if(vars.map[i][j] == 'E')
// 				mlx_put_image_to_window(vars.mlx, vars.win, vars.wall_img, x, y);
// 			else if(vars.map[i][j] == 'C')
// 				mlx_put_image_to_window(vars.mlx, vars.win, vars.coll_img, x, y);
// 			x+=distX;
// 			j++;
// 		}
		
// 		y+=distY;
// 		i++;
// 	}

// 	return (0);

// }

// int draw_next_frame(t_vars *vars)
// {
// 	// vars->color += 1;
// 	// int i = 0;
// 	// while(i < SCREENWIDTH)
// 	// {
// 	// 	int j = 0;
// 	// 	while(j < SCREENHEIGHT)
// 	// 	{
// 	// 		my_mlx_pixel_put(&vars->img, i, j, 0x00000000);
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }	
// 	if(vars->y + CHAR_HEIGHT > SCREENHEIGHT)
// 		vars->y = 1;
// 	if(vars->x + CHAR_WIDTH > SCREENWIDTH)
// 		vars->x = 1;
// 	if(vars->y < 1)
// 		vars->y = SCREENHEIGHT - CHAR_HEIGHT;
// 	if(vars->x < 1)
// 		vars->x = SCREENWIDTH - CHAR_WIDTH;
	
// 	//mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img, 0, 0);
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->char_img, vars->x, vars->y);
// 	mlx_string_put(vars->mlx, vars->win, 20,20, 0x00FF0000, "char *string");
// 	draw_map(*vars);
// 	//mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, vars->win);
// 	return (0);
// }



// int	move_pixel(int keycode, t_vars *vars)
// {
// 	if(keycode == KEY_ESC)
// 	{
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		exit(0);
// 	}
// 	if((keycode == KEY_UP || keycode == KEY_W)  && vars->y > 0)
// 		vars->y -=10;
// 	if((keycode == KEY_DOWN  || keycode == KEY_S) && vars->y < 1080)
// 		vars->y +=10;
// 	if((keycode == KEY_RIGHT || keycode == KEY_D) && vars->x < 1920)
// 		vars->x +=10;
// 	if((keycode == KEY_LEFT  || keycode == KEY_A) && vars->x > 0)
// 		vars->x -=10;

// 	//my_mlx_pixel_put(&vars->img, vars->x, vars->y, 0x00FF0000);
// 	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
// 	return (0);
// }

// int	close_window(t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	exit(0);
// }


// int	main(void)
// {
// 	//void	*mlx;
// 	//void	*mlx_win;
	
// 	//t_data	img;
// 	t_vars vars;
	
// 	vars.leg = check_map("map.ber");

// 	vars.map = read_map("map.ber", vars.leg);
// 	vars.x = 10;
// 	vars.y = 10;
// 	vars.color = 0x00000000;
	
// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
// 	vars.char_img = mlx_xpm_file_to_image(vars.mlx, "Vampire.xpm", &vars.img_width, &vars.img_height);
// 	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars.char_img);
// 	//vars.bg_img = mlx_xpm_file_to_image(vars.mlx, "bg_big.xpm", &vars.img_width, &vars.img_height);
// 	vars.wall_img = mlx_xpm_file_to_image(vars.mlx, "wall.xpm", &vars.img_width, &vars.img_height);
// 	vars.coll_img = mlx_xpm_file_to_image(vars.mlx, "coin.xpm", &vars.img_width, &vars.img_height);
// 	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars.char_img);
	
// 	mlx_hook(vars.win, 2, 1L<<0, move_pixel, &vars);
// 	mlx_hook(vars.win, 17, 1L<<17, close_window, &vars);
// 	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
// 	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
// 	  							&vars.img.endian);
// 	//my_mlx_pixel_put(&vars.img, vars.x, vars.y, 0x00FF0000);
// 	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
// 	//draw_map(vars);
// 	mlx_loop_hook(vars.mlx, draw_next_frame, &vars);
// 	mlx_loop(vars.mlx);
// }


	// int main()
	// {
		
	// 	int i = 0;
	// 	int j = 0;
	// 	if (map == NULL)
	// 		printf("map is null\n");
	// 	while (map[i] != NULL)
	// 	{
	// 		j = 0;
	// 		while (map[i][j] != '\0')
	// 		{
	// 			printf("%c", map[i][j]);
	// 			j++;
	// 		}
	// 		printf("\n");
	// 		i++;
	// 	}
	// 	return 0;
	// }


// int	main(void)
// {

//     void	*mlx;
//     void	*win;
//     void	*img;
//     char	*relative_path = "Vampire.xpm";
//     int		img_width;
//     int		img_height;
	

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//     img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
// 	printf("img: %p\n", img);
//     mlx_put_image_to_window(mlx, win, img, 0, 0);
//     mlx_loop(mlx);
// }
void print_map(char **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
int	main(void)
{
	
	t_vars vars;
	vars.leg = check_map("map.ber");
	vars.map = read_map("map.ber", vars.leg);
	
	print_map(vars.map, vars.leg.row, vars.leg.col);
}
	

