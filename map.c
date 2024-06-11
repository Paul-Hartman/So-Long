/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:37:28 by phartman          #+#    #+#             */
/*   Updated: 2024/06/06 19:01:25 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_legend	check_map(char *filename)
{
	t_legend	leg;
	char		buf;
	int			fd;

	leg.c_count = 0;
	leg.p_count = 0;
	leg.e_count = 0;
	leg.col = 0;
	leg.row = 1;
	if (!filename || !ft_strnstr(filename, ".ber", ft_strlen(filename)))
		print_error(FILE_FORMAT_ERROR);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error(FILE_OPEN_ERROR);
	while (read(fd, &buf, 1) > 0)
		count_symbols(buf, &leg);
	if (leg.p_count != 1 || leg.e_count != 1 || leg.c_count < 1)
		print_error(MAP_FORMAT_ERROR);
	close(fd);
	return (leg);
}

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}


void	save_positions(char buf, t_vars *vars, char **map)
{
	static int	row;
	static int	col;
	static int	i;
	t_coord		temp;

	if (buf == '\n')
	{
		row++;
		col = 0;
	}
	else
	{
		temp.x = col;
		temp.y = row;
		if (buf == 'P')
			vars->leg.p = temp;
		if (buf == 'E')
			vars->leg.e = temp;
		if (buf == 'C')
			vars->leg.c[i++] = temp;
		map[row][col] = buf;
		col++;
	}
}

char	**malloc_map(t_vars *vars)
{
	char	**map;
	int		row;

	row = 0;
	map = malloc(sizeof(char *) * vars->leg.row);
	malloc_protection(map);
	while (row < vars->leg.row)
	{
		map[row] = malloc(sizeof(char) * vars->leg.col +1);
		malloc_protection(map[row]);
		map[row][vars->leg.col] = '\0';
		row++;
	}
	return (map);
}

char	**read_map(char *filename, t_vars *vars)
{
	int		fd;
	char	**map;
	char	buf;

	map = malloc_map(vars);
	vars->leg.c = malloc(sizeof(t_coord) * vars->leg.c_count);
	malloc_protection(vars->leg.c);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error(FILE_OPEN_ERROR);
	while (read(fd, &buf, 1) > 0)
		save_positions(buf, vars, map);
	close(fd);
	if (!has_walls(map, vars->leg))
		print_error(WALL_ERROR);
	if (!is_rectangle(map, vars->leg))
		print_error(SHAPE_ERROR);
	if (!map_isvalidpath(map, vars->leg, vars))
		print_error(PATH_ERROR);
	return (map);
}

