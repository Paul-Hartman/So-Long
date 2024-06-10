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

void	lstremove_back(t_list **lst)
{
	t_list	*last;
	t_list	*node;

	if (lst && *lst)
	{
		last = ft_lstlast(*lst);
		node = *lst;
		if (node == last)
		{
			*lst = NULL;
		}
		else
		{
			while (node->next != last)
			{
				node = node->next;
			}
			node->next = NULL;
		}
		free(last);
	}
}

int	find_closest_coll(char **map, t_coord cur_pos, t_legend leg, int *collected)
{
	int	i;
	int	shortest_dist;
	int	dist;
	int	closest_collectable;

	shortest_dist = INT_MAX;
	i = 0;
	while (i < leg.c_count)
	{
		if (cur_pos.x == leg.c[i].x && cur_pos.y == leg.c[i].y)
			(*collected)++;
		if (map[leg.c[i].y][leg.c[i].x] != 'T')
		{
			dist = abs(cur_pos.x - leg.c[i].x) + abs(cur_pos.y - leg.c[i].y);
			if (dist < shortest_dist)
			{
				shortest_dist = dist;
				closest_collectable = i;
			}
		}
		i++;
	}
	return (closest_collectable);

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

t_coord	assign_coord(int x, int y)
{
	t_coord	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

// t_coord	*get_neighbors(char **map, t_coord current_pos, t_legend leg, int *valid_count)
// {
// 	t_coord			next_pos;
// 	const t_coord	directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
// 	t_coord		*valid_neighbors;
// 	int i;

// 	i = 0;
// 	*valid_count = 0;
// 	valid_neighbors = malloc(sizeof(t_coord) * 4);
// 	malloc_protection(valid_neighbors);
// 	while(i < 4)
// 	{
// 		next_pos.x = current_pos.x + directions[i].x;
// 		next_pos.y = current_pos.y + directions[i].y;
// 		i++;
// 		if (next_pos.x < 0 || next_pos.x >= leg.col || next_pos.y < 0 || next_pos.y >= leg.row)
// 			continue;
// 		if (map[next_pos.y][next_pos.x] == 'F' || map[next_pos.y][next_pos.x] == 'E' || map[next_pos.y][next_pos.x] == 'T')
// 			valid_neighbors[(*valid_count)++] = next_pos;
// 	}
// 	return (valid_neighbors);

// }


// t_coord	get_best_neighbor(char **map, t_coord current_pos, t_legend leg)
// {
// 	int				i;
// 	int				j;
// 	int				shortest_dist;
// 	int				neighbor_dist;
// 	t_coord			chosen_pos;
// 	static int		collected;
// 	t_coord		*valid_neighbors;
// 	int valid_count;

// 	valid_neighbors = get_neighbors(map, current_pos, leg, &valid_count);
// 	chosen_pos = assign_coord(-1, -1);
// 	shortest_dist = INT_MAX;
// 	i = 0;
// 	if (collected < leg.c_count)
// 		j = find_closest_coll(map, current_pos, leg, &collected);
// 	while (i < valid_count)
// 	{
		
// 		if (collected == leg.c_count)
// 			neighbor_dist = abs(valid_neighbors[i].x - leg.e.x) + abs(valid_neighbors[i].y - leg.e.y);
// 		else
// 			neighbor_dist = abs(valid_neighbors[i].x - leg.c[j].x) + abs(valid_neighbors[i].y - leg.c[j].y);
// 		if (neighbor_dist < shortest_dist)
// 		{
// 			shortest_dist = neighbor_dist;
// 			chosen_pos = valid_neighbors[i];
// 		}
// 		i++;
		
// 	}
// 	return (chosen_pos);
// }

t_coord	get_neighbors(char **map, t_coord current_pos, t_legend leg)
{
	int				i;
	int				j;
	int				shortest_dist;
	int				neighbor_dist;
	const t_coord	directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	t_coord			next_pos;
	t_coord			chosen_pos;
	static int		collected;

	next_pos = assign_coord(0, 0);
	chosen_pos = assign_coord(-1, -1);
	shortest_dist = INT_MAX;
	i = 0;
	if (collected < leg.c_count)
		j = find_closest_coll(map, current_pos, leg, &collected);
	while (i < 4)
	{
		next_pos.x = current_pos.x + directions[i].x;
		next_pos.y = current_pos.y + directions[i].y;
		if (next_pos.x < 0 || next_pos.x >= leg.col || next_pos.y < 0 || next_pos.y >= leg.row)
		{
			i++;
			continue;
		}
		if (map[next_pos.y][next_pos.x] == 'F' || map[next_pos.y][next_pos.x] == 'E' || map[next_pos.y][next_pos.x] == 'T')
		{
			if (collected == leg.c_count)
				neighbor_dist = abs(next_pos.x - leg.e.x) + abs(next_pos.y - leg.e.y);
			else
				neighbor_dist = abs(next_pos.x - leg.c[j].x) + abs(next_pos.y - leg.c[j].y);
			if (neighbor_dist < shortest_dist)
			{
				shortest_dist = neighbor_dist;
				chosen_pos = next_pos;
			}
		}
		i++;
	}
	return (chosen_pos);
}

void	malloc_protection(void *ptr)
{
	if (ptr == NULL)
		print_error(MALLOC_ERROR);
}

int	search_path(char **map, t_list *queue, t_coord current_pos)
{
	t_coord			*pos_copy;

	if (current_pos.x == -1 && current_pos.y == -1 && queue)
	{
		pos_copy = ft_lstlast(queue)->content;
		current_pos = *pos_copy;
		free(pos_copy);
		lstremove_back(&queue);
		return (-1);
	}
	else if (map[current_pos.y][current_pos.x] == 'E')
	{
		ft_lstclear(&queue, free);
		return (0);
	}
	else
	{
		map[current_pos.y][current_pos.x] = 'T';
		pos_copy = malloc(sizeof(t_coord));
		malloc_protection(pos_copy);
		*pos_copy = current_pos;
		ft_lstadd_back(&queue, ft_lstnew(pos_copy));
		return (1);
	}
}

int	greedy_best_search(char **map, t_legend leg)
{
	t_coord	current_pos;
	t_coord	*pos_copy;
	t_list	*queue;
	int		steps;
	int		i;

	steps = 0;
	current_pos = leg.p;
	pos_copy = malloc(sizeof(t_coord));
	malloc_protection(pos_copy);
	*pos_copy = current_pos;
	map[current_pos.y][current_pos.x] = 'T';
	queue = ft_lstnew(pos_copy);
	malloc_protection(queue);
	while (queue)
	{
		current_pos = get_neighbors(map, current_pos, leg);
		i = search_path(map, queue, current_pos);
		steps += i;
		if (i == 0)
			return (steps);
	}
	ft_lstclear(&queue, free);
	return (0);
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
	free_map(path_map, leg.row);
	return (vars->par = steps);
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
