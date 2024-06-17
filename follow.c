
#include "game.h"

// t_coord	*copy_position(t_coord current_pos)
// {
// 	t_coord	*pos_copy;

// 	pos_copy = malloc(sizeof(t_coord));
// 	malloc_protection(pos_copy);
// 	*pos_copy = current_pos;
// 	return (pos_copy);
// }

void	save_path(t_coord current_pos, t_vars *vars)
{
	t_path	*path;

	malloc_protection(path = malloc(sizeof(t_path)));

	path->dir = vars->direction;
	path->pos = current_pos;
	ft_lstadd_front(&vars->path, ft_lstnew(path));
	if (ft_lstsize(vars->path) > vars->points + 1)
	{
		lstremove_back(&vars->path);
	}

}


void	place_zombies(t_vars *vars)
{
	t_list	*path;
	t_coord	pos;
	t_direction	dir;

	path = vars->path;
	while (path)
	{
		pos = ((t_path *)path->content)->pos;
		dir = ((t_path *)path->content)->dir;
		if (dir == UP)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.up[vars->step], pos.x, pos.y);
		if (dir == DOWN)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.down[vars->step], pos.x, pos.y);
		if (dir == RIGHT)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.right[vars->step], pos.x, pos.y);
		if (dir == LEFT)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->sprites.zombie.left[vars->step], pos.x, pos.y);

		path = path->next;
	}

}

t_player	save_zomb_sprites(t_vars *vars)
{
	t_player		player;
	int				width;
	int				height;

	player.down[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_dn1.xpm", &width, &height);
	player.down[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_dn2.xpm", &width, &height);
	player.up[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_up1.xpm", &width, &height);
	player.up[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_up2.xpm", &width, &height);
	player.left[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_lf1.xpm", &width, &height);
	player.left[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_lf2.xpm", &width, &height);
	player.right[0] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_rt1.xpm", &width, &height);
	player.right[1] = mlx_xpm_file_to_image(vars->mlx,
			"./textures/zm_rt2.xpm", &width, &height);
	return (player);
}
