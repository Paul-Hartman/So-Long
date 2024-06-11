#include "test.h"


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


// int main(int argc, char const *argv[])
// {
//     t_vars vars;
//     vars.leg = check_map("map.ber");
// 	vars.map = read_map("map.ber", &vars);
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

// t_coord	get_best_neighbor(char **map, t_coord current_pos, t_legend *leg)
// {
// 	int				j;
// 	int				min_dist;
// 	t_coord			chosen_pos;
// 	t_coord			*valid_neighbors;
// 	int				valid_count;

// 	valid_neighbors = get_neighbors(map, current_pos, *leg, &valid_count);
// 	chosen_pos = assign_coord(-1, -1);
// 	min_dist = INT_MAX;
// 	if (leg->collected < leg->c_count)
// 		j = find_closest_coll(map, current_pos, leg);
// 	while (valid_count)
// 	{
// 		if (leg->collected == leg->c_count)
// 			min_dist = get_shortest(valid_neighbors[valid_count],
// 					leg->e, &chosen_pos, min_dist);
// 		else if (get_dist(valid_neighbors[valid_count], leg->c[j]) < min_dist)
// 			min_dist = get_shortest(valid_neighbors[valid_count],
// 					leg->c[j], &chosen_pos, min_dist);
// 		valid_count--;
// 	}
// 	free(valid_neighbors);
// 	return (chosen_pos);
// }

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

