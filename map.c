/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:28 by phartman          #+#    #+#             */
/*   Updated: 2024/05/30 15:14:53 by phartman         ###   ########.fr       */
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
	int c_count;
	int obst_count;
	p_count = 0;
	c_count = 0;
	e_count = 0;
	obst_count = 0;
	if (!filename || !ft_strnstr(filename, ".ber", ft_strlen(filename)))
		exit (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit (0);
	leg.col = 0;
	leg.row = 0;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			leg.row++;
		if (buf == '0' || buf == '1' || buf == 'C' || buf == 'E' || buf == 'P')
		{
			leg.col++;
			if (buf == 'P')
				p_count++;
			if (buf == 'E')
				e_count++;
			if (buf == 'C')
				c_count++;
			if(buf == '1')
				obst_count++;
		}
	}
	if(p_count != 1 || e_count != 1 || c_count < 1 || obst_count < 2*(leg.col -1) + (leg.row -1))
		exit(0);
	close(fd);
	return (leg);
}


char **read_map(char *filename, t_legend leg)
{
	int fd;
	char **map;
	char buf;
	int row;
	int col;
	
	row = 0;
	col = 0;
	map = malloc(sizeof(char *) * leg.row);
	while(row < leg.row)
	{
		map[row] = malloc(sizeof(char) * leg.col);
		row++;
	}
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
			map[row][col] = buf;
			col++;
		}
	}
	close(fd);
	return (map);
}



char	*add_to_string(char *str, char *buf)
{
	char	*newstr;
	int		size;

	if (!str || !buf)
		return (NULL);
	size = ft_strlen(str) + ft_strlen(buf) + 1;
	newstr = malloc(size);
	ft_bzero(newstr, size);
	ft_strlcat(newstr, str, size);
	ft_strlcat(newstr, buf, size);
	free(str);
	return (newstr);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_next_frame(t_vars *vars)
{
	// vars->color += 1;
	// int i = 0;
	// while(i < SCREENWIDTH)
	// {
	// 	int j = 0;
	// 	while(j < SCREENHEIGHT)
	// 	{
	// 		my_mlx_pixel_put(&vars->img, i, j, 0x00000000);
	// 		j++;
	// 	}
	// 	i++;
	// }	
	if(vars->y + CHAR_HEIGHT > SCREENHEIGHT)
		vars->y = 1;
	if(vars->x + CHAR_WIDTH > SCREENWIDTH)
		vars->x = 1;
	if(vars->y < 1)
		vars->y = SCREENHEIGHT - CHAR_HEIGHT;
	if(vars->x < 1)
		vars->x = SCREENWIDTH - CHAR_WIDTH;
	
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->char_img, vars->x, vars->y);
	mlx_string_put(vars->mlx, vars->win, 20,20, 0x00FF0000, "char *string");
	//mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, vars->win);
	return (0);
}



int	move_pixel(int keycode, t_vars *vars)
{
	if(keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if((keycode == KEY_UP || keycode == KEY_W)  && vars->y > 0)
		vars->y -=10;
	if((keycode == KEY_DOWN  || keycode == KEY_S) && vars->y < 1080)
		vars->y +=10;
	if((keycode == KEY_RIGHT || keycode == KEY_D) && vars->x < 1920)
		vars->x +=10;
	if((keycode == KEY_LEFT  || keycode == KEY_A) && vars->x > 0)
		vars->x -=10;

	//my_mlx_pixel_put(&vars->img, vars->x, vars->y, 0x00FF0000);
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}


// int	main(void)
// {
// 	//void	*mlx;
// 	//void	*mlx_win;
// 	t_vars	vars;
// 	//t_data	img;
	
// 	vars.x = 10;
// 	vars.y = 10;
// 	vars.color = 0x00000000;
	
// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
// 	vars.char_img = mlx_xpm_file_to_image(vars.mlx, "Vampire.xpm", &vars.img_width, &vars.img_height);
// 	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars.char_img);
// 	vars.bg_img = mlx_xpm_file_to_image(vars.mlx, "bg_big.xpm", &vars.img_width, &vars.img_height);
// 	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, vars.char_img);
	
// 	mlx_hook(vars.win, 2, 1L<<0, move_pixel, &vars);
// 	mlx_hook(vars.win, 17, 1L<<17, close_window, &vars);
// 	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
// 	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
// 	  							&vars.img.endian);
// 	//my_mlx_pixel_put(&vars.img, vars.x, vars.y, 0x00FF0000);
// 	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	
// 	mlx_loop_hook(vars.mlx, draw_next_frame, &vars);
// 	mlx_loop(vars.mlx);
// }

int main()
{
	char **map;
	t_legend leg;
	leg = check_map("map.ber");
	
	map = read_map("map.ber", leg);
	int i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
	return 0;
}


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
