#include "game.h"

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

