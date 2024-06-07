/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:41:44 by phartman          #+#    #+#             */
/*   Updated: 2024/06/06 19:47:00 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <fcntl.h>
#include <stdlib.h>
//#include <mlx.h>
#include "mlx/mlx.h"
#include <X11/Xlib.h>
#include "libft/libft.h"
#include <stdio.h>
#include <X11/keysym.h>


# define KEY_UP 65362
# define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

#define CHAR_WIDTH 16
#define CHAR_HEIGHT 16

# define XPM_ERROR	"Failed to load sprites\n"
# define MLX_INIT_ERROR	"mlx init error\n"
# define MLX_WINDOW_ERROR	"mlx_new_window() failed\n"



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

typedef struct s_sprites {
	void	*player;
	void	*ground;
	void 	*start;
	void	*wall;
	void	*coll;
	void	*exit;
}		t_sprites;

 typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int moves;
	int points;
	int par;
	t_data	img;
	t_sprites sprites;
	int		img_w;
    int		img_h;
	int screenwidth;
	int screenheight;
	t_legend leg;
	char **map;
	
}				t_vars;

char **read_map(char *filename, t_vars *vars);
int is_rectangle(char **map, t_legend leg);
int has_walls(char **map, t_legend leg);
int map_isvalidpath(char **map, t_legend leg, t_vars *vars);
t_coord get_neighbors(char **map, t_coord current_pos, t_legend leg);
int greedy_best_search(char **map, t_legend leg);
void free_map(char **map, int rows) ;
int find_closest_collectable(char **map, t_coord current_pos, t_legend leg, int *collected);
int	process_key_stroke(int keycode, t_vars *vars);

void lstremove_back(t_list **lst);
void print_map(char **map, int rows, int cols);
t_legend check_map(char *filename);
t_vars init();
int draw_next_frame(t_vars *vars);
int	move_charachter(int new_x, int new_y, t_vars *vars);
int	close_window(t_vars *vars);
void collision(t_vars *vars);
void draw_map(t_vars vars);


#endif