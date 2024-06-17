/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:41:44 by phartman          #+#    #+#             */
/*   Updated: 2024/06/13 16:22:51 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include "mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_ESC 65307

# define CHAR_WIDTH 32
# define CHAR_HEIGHT 32

# define MAX_MOVES 100
# define MOVES_BAR_WIDTH 100
# define MOVES_BAR_HEIGHT 10
# define POINTS_BAR_HEIGHT 17
# define POINTS_BAR_WIDTH 65

# define XPM_ERROR "Failed to load sprites\n"
# define MLX_INIT_ERROR "mlx init error\n"
# define MLX_WINDOW_ERROR "mlx_new_window() failed\n"
# define AGUMENT_ERROR "Wrong number of arguments\n"
# define WALL_ERROR "The map is not surrounded by walls\n"
# define SHAPE_ERROR "The map is not a rectangle\n"
# define PATH_ERROR "The map does not have a valid path\n"
# define BAD_CHAR_ERROR "The map contains invalid characters\n"
# define MAP_FORMAT_ERROR "The map has incorrect number of map symbols\n"
# define FILE_FORMAT_ERROR "Incorrect file format, must be .ber\n"
# define FILE_OPEN_ERROR "File failed to open\n"
# define MALLOC_ERROR "Malloc failed\n"

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}				t_direction;

typedef struct s_enemy
{
	t_coord		pos;
	t_coord		point_a;
	t_coord		point_b;
	t_coord		prev_pos;
	int			x;
	int			y;
	t_coord		target;
}				t_enemy;

typedef struct s_legend
{
	int			col;
	int			row;
	int			c_count;
	int			p_count;
	int			e_count;
	int			o_count;
	t_coord		p;
	t_coord		e;
	t_coord		*c;
}				t_legend;

typedef struct s_path
{
	t_coord		pos;
	t_direction	dir;

}				t_path;

typedef struct s_player
{
	void		*up[2];
	void		*down[2];
	void		*left[2];
	void		*right[2];
}				t_player;

typedef struct s_sprites
{
	t_player	player;
	void		*ground;
	void		*start;
	void		*coll;
	void		*enemy;
	t_player	zombie;
	void		*ui_moves;
	void		*ui_points;
	void		*wall_corner;
	void		*wall_horiz;
	void		*wall_vert;
	void		*tree;
	void		*gate_open;
	void		*gate_closed;
}				t_sprites;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			step;
	int			x;
	int			y;
	t_direction	direction;
	int			moves;
	int			points;
	t_list		*path;
	t_data		img;
	t_sprites	sprites;
	t_enemy		enemy;
	int			img_w;
	int			img_h;
	int			screenwidth;
	int			screenheight;
	t_legend	leg;
	char		**map;
}				t_vars;

// map.c
t_legend		check_map(char *filename);
char			**read_map(char *filename, t_vars *vars);
void			save_positions(char buf, t_vars *vars, char **map);
char			**malloc_map(t_vars *vars);
void			free_map(char **map, int rows);

// validation.c
int				is_rectangle(char **map, t_legend leg);
int				has_walls(char **map, t_legend leg);
void			count_symbols(char buf, t_legend *leg);
int				check_fill(char **map, t_legend leg);
int				map_isvalidpath(char **map, t_legend leg, t_vars *vars);

// rendering.c
t_vars			init(char *file);
int				draw_next_frame(t_vars *vars);
void			draw_map(t_vars vars);
void			place_sprite(t_vars vars, char sym, int x, int y);
void			place_obstacle(t_vars vars, int x, int y);

// game.c
int				process_key_stroke(int keycode, t_vars *vars);
int				move_charachter(int new_x, int new_y, t_vars *vars);
int				close_window(t_vars *vars);
void			collision(t_vars *vars);

// utils.c
void			lstremove_back(t_list **lst);
void			print_error(char *error_msg);
void			malloc_protection(void *ptr, char *error_msg);
t_coord			assign_coord(int x, int y);
int				flood_fill(char **map, t_coord pos, int row_max, int col_max);

// animation.c
void			player_anim(t_vars *vars);
void			save_path(t_coord current_pos, t_vars *vars);
void			place_zombies(t_vars *vars);
void			destroy_images(t_vars *vars);
void			destroy_char_images(t_vars *vars);

// ui.c
void			draw_ui(t_vars *vars);
void			draw_string(t_vars *vars, char *str, int x, int y);
void			draw_bar(t_vars *vars, int width, int height, t_coord start);
void			draw_progress_bars(t_vars *vars);

// enemy.c
int				enemy_init(t_vars *vars);
t_coord			pick_enemy_spaces(t_vars *vars, int direction);
void			switch_targets(t_enemy *enemy);
void			update_enemy(t_enemy *enemy, t_vars *vars);
void			move_enemy(t_enemy *enemy, t_vars *vars, int new_x, int new_y);

// image_handling.c
t_player		save_char_sprites(t_vars *vars);
void			save_images(t_vars *vars);
void			save_obstacle_sprites(t_vars *vars, t_sprites *sprite);
t_player		save_zomb_sprites(t_vars *vars);
void			xpm_check(t_sprites sprites);

#endif