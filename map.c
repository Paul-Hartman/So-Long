/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:28 by phartman          #+#    #+#             */
/*   Updated: 2024/05/27 18:15:43 by phartman         ###   ########.fr       */
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


// void draw_next_frame(t_vars vars)
// {
// 	int color1 = 0x00FF0000; // Red
// 	int color2 = 0x0000FF00; // Green
// 	int square_size = 100;
// 	int square_x = 100;
// 	int square_y = 100;
// 	printf("x = %d\n", vars.x);
// 	printf("y = %d\n", vars.y);
// 	for (int i = square_x; i < square_x + square_size; i++) 
// 	{
// 		for (int j = square_y; j < square_y + square_size; j++) 
// 		{
// 			int color;
// 			if ((i / 100) % 2 == (j / 1) % 2) 
// 			{
// 				color = color1;
// 			}
// 			else
// 				color = color2;
		
// 		my_mlx_pixel_put(vars.img.img, i, j, color);
// 		}
// 	}
// 	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);

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
	if(keycode == 32)
		mlx_destroy_window(vars->mlx, vars->win);;
	if(keycode == KEY_UP)
		vars->y +=1;
	if(keycode == KEY_DOWN && vars->y > 0)
		vars->y -=1;
	if(keycode == KEY_RIGHT)
		vars->x +=1;
	if(keycode == KEY_LEFT && vars->x > 0)
		vars->x -=1;

	printf("x = %d\n", vars->x);
	printf("y = %d\n", vars->y);
	my_mlx_pixel_put(&vars->img, vars->x, vars->y, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}



int	main(void)
{
	//void	*mlx;
	//void	*mlx_win;
	t_vars	vars;
	//t_data	img;
	vars.x = 0;
	vars.y = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, move_pixel, &vars);
	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
								&vars.img.endian);
	my_mlx_pixel_put(&vars.img, vars.x, vars.y, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
}




