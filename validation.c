#include "game.h"

int	is_rectangle(char **map, t_legend leg)
{
	size_t	length;
	int		i;

	i = 0;
	length = leg.col;
	while (i < leg.row)
	{
		if (ft_strlen(map[i]) != length)
			return (0);
		i++;
	}
	return (1);
}


int	has_walls(char **map, t_legend leg)
{
	int	i;

	i = 0;
	while (i < leg.col)
	{
		if (map[0][i] != '1' || map[leg.row - 1][i] != '1')
			return (0);
		if (i < leg.row)
		{
			if (map[i][0] != '1' || map[i][leg.col - 1] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

void	count_symbols(char buf, t_legend *leg)
{
	if (buf == '\n')
	{
		leg->col = 0;
		leg->row++;
	}
	else if (buf == '0' || buf == '1' || buf == 'C'
		|| buf == 'E' || buf == 'P')
	{
		leg->col++;
		if (buf == 'P')
			leg->p_count++;
		if (buf == 'E')
			leg->e_count++;
		if (buf == 'C')
			leg->c_count++;
	}
	else
		print_error(BAD_CHAR_ERROR);
}

int	map_isvalidpath(char **map, t_legend leg, t_vars *vars)
{
	int		i;
	int		steps;
	int		j;
	char	**path_map;

	path_map = malloc_map(vars);
	i = 0;
	while (i < leg.row)
	{
		j = 0;
		while (j < leg.col)
		{
			if (map[i][j] == '1')
				path_map[i][j] = 'N';
			else if (map[i][j] == 'E')
				path_map[i][j] = 'E';
			else
				path_map[i][j] = 'F';
			j++;
		}
		i++;
	}
	steps = greedy_best_search(path_map, leg);
	for (int i = 0; i < leg.row; i++) {
		for (int j = 0; j < leg.col; j++) {
			printf("%c", path_map[i][j]);
		}
		printf("\n");
	}
	free_map(path_map, leg.row);
	return (vars->par = steps);
}