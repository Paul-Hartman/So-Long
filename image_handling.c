#include "game.h"

t_player	save_char_sprites(t_vars *vars)
{
	t_player	player;
	int			width;
	int			height;

	player.down[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_dn1.xpm",
			&width, &height);
	player.down[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_dn2.xpm",
			&width, &height);
	player.up[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_up1.xpm",
			&width, &height);
	player.up[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_up2.xpm",
			&width, &height);
	player.left[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_lf1.xpm",
			&width, &height);
	player.left[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_lf2.xpm",
			&width, &height);
	player.right[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_rt1.xpm",
			&width, &height);
	player.right[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/pl_rt2.xpm",
			&width, &height);
	return (player);
}

void	save_images(t_vars *vars)
{
	t_sprites	sprite;
	int			width;
	int			height;

	sprite.player = save_char_sprites(vars);
	sprite.zombie = save_zomb_sprites(vars);
	save_obstacle_sprites(vars, &sprite);
	sprite.ground = mlx_xpm_file_to_image(vars->mlx, "./textures/ground.xpm",
			&width, &height);
	sprite.coll = mlx_xpm_file_to_image(vars->mlx, "./textures/collect.xpm",
			&width, &height);
	sprite.start = mlx_xpm_file_to_image(vars->mlx, "./textures/start.xpm",
			&width, &height);
	sprite.ui_points = mlx_xpm_file_to_image(vars->mlx,
			"./textures/points_UI.xpm", &width, &height);
	sprite.ui_moves = mlx_xpm_file_to_image(vars->mlx,
			"./textures/moves_UI.xpm", &width, &height);
	sprite.enemy = mlx_xpm_file_to_image(vars->mlx, "./textures/enemy.xpm",
			&width, &height);
	xpm_check(sprite);
	vars->sprites = sprite;
}

void	save_obstacle_sprites(t_vars *vars, t_sprites *sprite)
{
	int	width;
	int	height;

	sprite->wall_corner = mlx_xpm_file_to_image(vars->mlx,
			"./textures/wall_corner.xpm", &width, &height);
	sprite->wall_horiz = mlx_xpm_file_to_image(vars->mlx,
			"./textures/wall_horiz.xpm", &width, &height);
	sprite->wall_vert = mlx_xpm_file_to_image(vars->mlx,
			"./textures/wall_vert.xpm", &width, &height);
	sprite->tree = mlx_xpm_file_to_image(vars->mlx, "./textures/tree.xpm",
			&width, &height);
	sprite->gate_open = mlx_xpm_file_to_image(vars->mlx,
			"./textures/gate_open.xpm", &width, &height);
	sprite->gate_closed = mlx_xpm_file_to_image(vars->mlx,
			"./textures/gate_closed.xpm", &width, &height);
}

t_player	save_zomb_sprites(t_vars *vars)
{
	t_player	player;
	int			width;
	int			height;

	player.down[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_dn1.xpm",
			&width, &height);
	player.down[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_dn2.xpm",
			&width, &height);
	player.up[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_up1.xpm",
			&width, &height);
	player.up[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_up2.xpm",
			&width, &height);
	player.left[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_lf1.xpm",
			&width, &height);
	player.left[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_lf2.xpm",
			&width, &height);
	player.right[0] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_rt1.xpm",
			&width, &height);
	player.right[1] = mlx_xpm_file_to_image(vars->mlx, "./textures/zm_rt2.xpm",
			&width, &height);
	return (player);
}

void	xpm_check(t_sprites sprites)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (!sprites.player.down[i] || !sprites.player.up[i]
			|| !sprites.player.left[i] || !sprites.player.right[i]
			|| !sprites.zombie.down[i] || !sprites.zombie.up[i]
			|| !sprites.zombie.right[i] || !sprites.zombie.left[i]
			|| !sprites.ground || !sprites.coll || !sprites.start
			|| !sprites.enemy || !sprites.ui_moves || !sprites.ui_points
			|| !sprites.wall_corner || !sprites.wall_horiz || !sprites.wall_vert
			|| !sprites.tree || !sprites.gate_open || !sprites.gate_closed)
			print_error(XPM_ERROR);
		i++;
	}
}
