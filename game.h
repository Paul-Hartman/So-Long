/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:41:44 by phartman          #+#    #+#             */
/*   Updated: 2024/06/05 14:12:23 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <X11/Xlib.h>
#include "libft/libft.h"
#include <stdio.h>


# define KEY_UP 65362
# define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

#define CHAR_WIDTH 88
#define CHAR_HEIGHT 97

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED	3

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_coord {
	int x;
	int y;
}				t_coord;


typedef struct	s_legend {
	int col;
	int row;
	int c_count;
	t_coord p;
	t_coord e;
	t_coord *c;
}				t_legend;



 typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int color;
	t_data	img;
	void *bg_img;
	void	*char_img;
	void *wall_img;
	void *coll_img;
	int		img_width;
    int		img_height;
	t_legend leg;
	char **map;
	
}				t_vars;

int	mlx_sync(int cmd, void *ptr);