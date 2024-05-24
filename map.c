/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:28 by phartman          #+#    #+#             */
/*   Updated: 2024/05/24 19:34:34 by phartman         ###   ########.fr       */
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


void draw_next_frame(t_data *img)
{
	int color1 = 0x00FF0000; // Red
	int color2 = 0x0000FF00; // Green
	int square_size = 1000;
	int square_x = 100;
	int square_y = 100;
	for (int i = square_x; i < square_x + square_size; i++) 
	{
		for (int j = square_y; j < square_y + square_size; j++) 
		{
			int color;
			if ((i / 100) % 2 == (j / 1) % 2) 
			{
				color = color1;
			}
			else
				color = color2;
		
		my_mlx_pixel_put(img, i, j, color);
		}
	}

}

void double_buffering(t_data *img, void *mlx, void *win)
{
    t_data buffer;

    // Create a new image for the back buffer
    buffer.img = mlx_new_image(mlx, 1920, 1080);
    buffer.addr = mlx_get_data_addr(buffer.img, &buffer.bits_per_pixel, &buffer.line_length,
                                    &buffer.endian);

    // Draw the next frame to the back buffer
    draw_next_frame(&buffer);

    // Swap the buffers
    mlx_destroy_image(mlx, img->img);
    *img = buffer;

    // Display the new front buffer
    mlx_put_image_to_window(mlx, win, img->img, 0, 0);
}


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	
	
	t_data	img;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// Draw a square
	

	
	double_buffering(&img, mlx, mlx_win);
	mlx_loop(mlx);
}