/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:28 by phartman          #+#    #+#             */
/*   Updated: 2024/05/29 18:10:32 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"




// char *read_map(char *filename)
// {
// 	int fd;
// 	char *map;
// 	char *buf;
// 	int i;
// 	char *line ;
// 	line = "";
	
// 	if (!filename || !ft_strnstr(filename, ".ber"))
// 		return (NULL);
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (NULL);
// 	i = 0;
// 	while (read(fd, buf, 1) > 0)
// 	{
// 		ft_strlcat(map + i, line);
// 		i += ft_strlen(line);
// 		map[i] = '\n';
// 		i++;
// 		free(line);
// 	}
// 	map[i] = '\0';
// 	close(fd);
// 	return (map);
// }



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
	//vars->color += 1;
	// vars->x += 1;
	// vars->y += 1;
	//int i = 0;
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
	
	if(vars->y + 100 > SCREENHEIGHT)
		vars->y = 0;
	if(vars->x + 100 > SCREENWIDTH)
		vars->x = 0;
	
	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->char_img, vars->x, vars->y);
	return (0);
}
// int draw_next_frame(t_vars *vars)
// {
// 	int color1 = 0x00FFFFFF;
// 	int color2 = 0x00000000;
// 	mlx_clear_window(vars->mlx, vars->win);
// 	int square_size = 1;
// 	if(vars->x + square_size > 1920)
// 		vars->x = 0;
// 	if(vars->y + square_size > 1080)
// 		vars->y = 0;
// 	vars->x += 1;
// 	vars->y += 1;
	
// 	int square_x = vars->x;
// 	int square_y = vars->y;
// 	for (int i = square_x; i < square_x + square_size; i++) 
// 	{
// 		for (int j = square_y; j < square_y + square_size; j++) 
// 		{
// 			int color;
// 			if ((i / 100) % 2 == (j / 10) % 2) 
// 			{
// 				color = color1;
// 			}
// 			else
// 				color = color2;
		
// 		my_mlx_pixel_put(vars->img.img, i, j, color);
// 		}
// 	}
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
// 	return (0);
	

// }

// void double_buffering(t_vars *vars)
// {
//     t_data buffer;

//     // Create a new image for the back buffer
//     buffer.img = mlx_new_image(vars->mlx, 1920, 1080);
//     buffer.addr = mlx_get_data_addr(buffer.img, &buffer.bits_per_pixel, &buffer.line_length,
//                                     &buffer.endian);

//     // Draw the next frame to the back buffer
//     draw_next_frame(*vars);

//     // Swap the buffers
//     mlx_destroy_image(vars->mlx, vars->img.img);
// 	vars->img.img = buffer.img;

//     // Display the new front buffer
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    
// }


int	move_pixel(int keycode, t_vars *vars)
{
	if(keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if(keycode == KEY_UP  && vars->y > 0)
		vars->y -=10;
	if(keycode == KEY_DOWN && vars->y < 1080)
		vars->y +=10;
	if(keycode == KEY_RIGHT && vars->x < 1920)
		vars->x +=10;
	if(keycode == KEY_LEFT && vars->x > 0)
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


int	main(void)
{
	//void	*mlx;
	//void	*mlx_win;
	t_vars	vars;
	//t_data	img;
	
	vars.x = 0;
	vars.y = 0;
	vars.color = 0x00000000;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	vars.char_img = mlx_xpm_file_to_image(vars.mlx, "Vampire.xpm", &vars.img_width, &vars.img_height);
	vars.bg_img = mlx_xpm_file_to_image(vars.mlx, "bg_big.xpm", &vars.img_width, &vars.img_height);
	mlx_hook(vars.win, 2, 1L<<0, move_pixel, &vars);
	mlx_hook(vars.win, 17, 1L<<17, close_window, &vars);
	//  vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
	//  vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
	//  							&vars.img.endian);
	//my_mlx_pixel_put(&vars.img, vars.x, vars.y, 0x00FF0000);
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop_hook(vars.mlx, draw_next_frame, &vars);
	mlx_loop(vars.mlx);
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
