#include "game.h"

int	main(int argc, char const *argv[])
{
	t_vars	vars;

	if (argc != 2)
		print_error(AGUMENT_ERROR);
	vars = init(argv[1]);
	printf("vars.par = %d\n", vars.par);
	mlx_hook(vars.win, 2, 1L << 0, process_key_stroke, &vars);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_loop_hook(vars.mlx, draw_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
