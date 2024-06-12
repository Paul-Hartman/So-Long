#include "game.h"

int find_ideal_path(char **map, t_legend leg, t_vars *vars)
{
	int		i;
	int		steps;
	int		j;
	char	**path_map;

	steps = 1;
	path_map = malloc_map(vars);
	i = 0;
	print_map(map, leg.row, leg.col);
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
	steps = greedy_best_search(path_map, leg, vars);
	print_map(path_map, leg.row, leg.col);
	printf("steps: %d\n", steps);
	free_map(path_map, leg.row);
	return (steps);
}

int	greedy_best_search(char **map, t_legend leg, t_vars *vars)
{
	t_coord	current_pos;
	t_coord	*pos_copy;
	t_list	*queue;
	int		steps;
	int		i;
	vars->collected = 0;
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
		current_pos = get_best_neighbor(map, current_pos, leg, &vars->collected);
		i = search_path(map, queue, current_pos);
		steps += i;
		if (i == 0)
			return (steps);
	}
	ft_lstclear(&queue, free);
	return (0);
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
			dist = get_dist(cur_pos, leg.c[i]);
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

// t_coord	get_neighbors(char **map, t_coord current_pos, t_legend leg)
// {
// 	int				i;
// 	int				j;
// 	int				shortest_dist;
// 	int				neighbor_dist;
// 	const t_coord	directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
// 	t_coord			next_pos;
// 	t_coord			chosen_pos;
// 	static int		collected;

// 	next_pos = assign_coord(0, 0);
// 	chosen_pos = assign_coord(-1, -1);
// 	shortest_dist = INT_MAX;
// 	i = 0;
// 	if (collected < leg.c_count)
// 		j = find_closest_coll(map, current_pos, leg, &collected);
// 	while (i < 4)
// 	{
// 		next_pos.x = current_pos.x + directions[i].x;
// 		next_pos.y = current_pos.y + directions[i].y;
// 		if (next_pos.x < 0 || next_pos.x >= leg.col || next_pos.y < 0 || next_pos.y >= leg.row)
// 		{
// 			i++;
// 			continue;
// 		}
// 		if (map[next_pos.y][next_pos.x] == 'F' || map[next_pos.y][next_pos.x] == 'E' || map[next_pos.y][next_pos.x] == 'T')
// 		{
// 			if (collected == leg.c_count)
// 				neighbor_dist = abs(next_pos.x - leg.e.x) + abs(next_pos.y - leg.e.y);
// 			else
// 				neighbor_dist = abs(next_pos.x - leg.c[j].x) + abs(next_pos.y - leg.c[j].y);
// 			if (neighbor_dist < shortest_dist)
// 			{
// 				shortest_dist = neighbor_dist;
// 				chosen_pos = next_pos;
// 			}
// 		}
// 		i++;
// 	}
// 	return (chosen_pos);
// }



// t_coord	get_neighbors(char **map, t_coord current_pos, t_legend leg)
// {
// 	int				i;
// 	int				j;
// 	int				shortest_dist;
// 	int				neighbor_dist;
// 	const t_coord	directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
// 	t_coord			next_pos;
// 	t_coord			chosen_pos;
// 	static int		collected;

// 	next_pos = assign_coord(0, 0);
// 	chosen_pos = assign_coord(-1, -1);
// 	shortest_dist = INT_MAX;
// 	i = 0;
// 	if (collected < leg.c_count)
// 		j = find_closest_coll(map, current_pos, leg, &collected);
// 	while (i < 4)
// 	{
// 		next_pos.x = current_pos.x + directions[i].x;
// 		next_pos.y = current_pos.y + directions[i].y;
// 		if (next_pos.x < 0 || next_pos.x >= leg.col || next_pos.y < 0 || next_pos.y >= leg.row)
// 		{
// 			i++;
// 			continue;
// 		}
// 		if (map[next_pos.y][next_pos.x] == 'F' || map[next_pos.y][next_pos.x] == 'E' || map[next_pos.y][next_pos.x] == 'T')
// 		{
// 			if (collected == leg.c_count)
// 				neighbor_dist = abs(next_pos.x - leg.e.x) + abs(next_pos.y - leg.e.y);
// 			else
// 				neighbor_dist = abs(next_pos.x - leg.c[j].x) + abs(next_pos.y - leg.c[j].y);
// 			if (neighbor_dist < shortest_dist)
// 			{
// 				shortest_dist = neighbor_dist;
// 				chosen_pos = next_pos;
// 			}
// 		}
// 		i++;
// 	}
// 	return (chosen_pos);
// }


#include "game.h"


// int	find_closest_coll(char **map, t_coord cur_pos, t_legend *leg)
// {
// 	int	i;
// 	int	shortest_dist;
// 	int	dist;
// 	int	closest_collectable;

// 	shortest_dist = INT_MAX;
// 	i = 0;
// 	while (i < leg->c_count)
// 	{
// 		if (cur_pos.x == leg->c[i].x && cur_pos.y == leg->c[i].y)
// 			leg->collected++;
// 		if (map[leg->c[i].y][leg->c[i].x] != 'T')
// 		{
// 			dist = get_dist(cur_pos, leg->c[i]);
// 			if (dist < shortest_dist)
// 			{
// 				shortest_dist = dist;
// 				closest_collectable = i;
// 			}
// 		}
// 		i++;
// 	}
// 	printf("collected = %d\n", leg->collected);
// 	return (closest_collectable);
// }

// int	get_shortest(t_coord cur_pos, t_coord target_pos, 
// t_coord *chosen_pos, int min_dist)
// {
// 	if (get_dist(cur_pos, target_pos) < min_dist)
// 	{
// 		min_dist = get_dist(cur_pos, target_pos);
// 		*chosen_pos = cur_pos;
// 	}
// 	else if (get_dist(cur_pos, target_pos) < min_dist)
// 	{
// 		min_dist = get_dist(cur_pos, target_pos);
// 		*chosen_pos = cur_pos;
// 	}
// 	return (min_dist);
// }

// t_coord	*get_neighbors(char **map, t_coord current_pos,
// t_legend leg, int *valid_count)
// {
// 	t_coord			next_pos;
// 	const t_coord	directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
// 	t_coord			*valid_neighbors;
// 	int				i;

// 	i = 0;
// 	*valid_count = 0;
// 	valid_neighbors = malloc(sizeof(t_coord) * 4);
// 	malloc_protection(valid_neighbors);
// 	while (i < 4)
// 	{
// 		next_pos.x = current_pos.x + directions[i].x;
// 		next_pos.y = current_pos.y + directions[i].y;
// 		i++;
// 		if (next_pos.x < 0 || next_pos.x >= leg.col
// 			|| next_pos.y < 0 || next_pos.y >= leg.row)
// 			continue ;
// 		if (map[next_pos.y][next_pos.x] == 'F' ||
// 			map[next_pos.y][next_pos.x] == 'T' ||
// 			map[next_pos.y][next_pos.x] == 'E')
// 			valid_neighbors[(*valid_count)++] = next_pos;
// 	}
// 	return (valid_neighbors);
// }


t_coord	*get_nbrs(char **map, t_coord current_pos,
t_legend leg, int *valid_count)
{
	t_coord			next_pos;
	const t_coord	directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	t_coord			*valid_neighbors;
	int				i;

	i = 0;
	*valid_count = 0;
	valid_neighbors = malloc(sizeof(t_coord) * 4);
	valid_neighbors[0] = assign_coord(-1, -1);
	malloc_protection(valid_neighbors);
	while (i < 4)
	{
		next_pos.x = current_pos.x + directions[i].x;
		next_pos.y = current_pos.y + directions[i].y;
		i++;
		if (next_pos.x < 0 || next_pos.x >= leg.col
			|| next_pos.y < 0 || next_pos.y >= leg.row)
			continue ;
		if (map[next_pos.y][next_pos.x] == 'F'
		|| map[next_pos.y][next_pos.x] == 'E')
			valid_neighbors[(*valid_count)++] = next_pos;
	}
	return (valid_neighbors);
}


int	get_shortest(t_coord cur_pos, t_coord target_pos, 
t_coord *chosen_pos, int min_dist)
{
	if (get_dist(cur_pos, target_pos) < min_dist)
	{
		min_dist = get_dist(cur_pos, target_pos);
		*chosen_pos = cur_pos;
	}
	return (min_dist);
}



t_coord	get_best_neighbor(char **map, t_coord current_pos, t_legend leg, int *coll)
{
	int				j;
	int				min_dist;
	t_coord			chosen_pos;
	t_coord			*valid_neighbors;
	int				valid_count;

	valid_neighbors = get_nbrs(map, current_pos, leg, &valid_count);
	chosen_pos = assign_coord(-1, -1);
	min_dist = INT_MAX;
	if (*coll < leg.c_count)
		j = find_closest_coll(map, current_pos, leg, coll);
	while (valid_count >= 0)
	{
		if (*coll == leg.c_count)
			min_dist = get_shortest(valid_neighbors[valid_count],
					leg.e, &chosen_pos, min_dist);
		else
			min_dist = get_shortest(valid_neighbors[valid_count], leg.c[j], &chosen_pos, min_dist);
		valid_count--;
	}
	free(valid_neighbors);
	return (chosen_pos);
}

// t_coord	get_best_neighbor(char **map, t_coord current_pos, t_legend leg)
// {
// 	int				j;
// 	int				shortest_dist;
// 	int				neighbor_dist;
// 	t_coord			chosen_pos;
// 	static int		collected;
// 	t_coord			*valid_neighbors;
// 	int valid_count;

// 	valid_neighbors = get_neighbors(map, current_pos, leg, &valid_count);
// 	chosen_pos = assign_coord(-1, -1);
// 	shortest_dist = INT_MAX;
// 	if (collected < leg.c_count)
// 		j = find_closest_coll(map, current_pos, leg, &collected);
// 	while (valid_count)
// 	{
// 		if (collected == leg.c_count)
// 			neighbor_dist = abs(valid_neighbors[valid_count].x - leg.e.x) + abs(valid_neighbors[valid_count].y - leg.e.y);
// 		else
// 			neighbor_dist = abs(valid_neighbors[valid_count].x - leg.c[j].x) + abs(valid_neighbors[valid_count].y - leg.c[j].y);
// 		if (neighbor_dist < shortest_dist)
// 		{
// 			shortest_dist = neighbor_dist;
// 			chosen_pos = valid_neighbors[valid_count];
// 		}
// 		valid_count--;
// 	}
// 	free(valid_neighbors);
// 	return (chosen_pos);
// }

