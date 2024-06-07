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


t_legend check_map(char *filename)
{
	int fd;
	t_legend leg;
	char buf;
	int p_count;
	int e_count;
	int obst_count;
	p_count = 0;
	leg.c_count = 0;
	e_count = 0;
	obst_count = 0;
	if (!filename || !ft_strnstr(filename, ".ber", ft_strlen(filename)))
	{
		printf("wrong file Error\n");
		exit (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("read Error\n");
		exit (0);
	}
	leg.col = 0;
	leg.row = 1;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
		{
			leg.col = 0;
			leg.row++;
		}
		else if (buf == '0' || buf == '1' || buf == 'C' || buf == 'E' || buf == 'P')
		{
			leg.col++;
			if (buf == 'P')
				p_count++;
			if (buf == 'E')
				e_count++;
			if (buf == 'C')
				leg.c_count++;
			if(buf == '1')
				obst_count++;
		}
		else
		{
			printf("map error Error\n");
			exit (0);
		}
	}
	if(p_count != 1 || e_count != 1 || leg.c_count < 1 || obst_count < 2*((leg.col -1) + (leg.row -1)))
	{
		
		printf("map error Error\n");
		exit (0);
	}
	// printf("leg.col: %d\n", leg.col);
	// 	printf("leg.row: %d\n", leg.row);
	// 	printf("p_count: %d\n", p_count);
	// 	printf("e_count: %d\n", e_count);
	// 	printf("c_count: %d\n", leg.c_count);
	// 	printf("expeced obst_count: %d\n", 2*((leg.col -1) + (leg.row -1)));	
	// 	printf("obst_count: %d\n", obst_count);
	close(fd);
	return (leg);
}

void print_map(char **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}


void lstremove_back(t_list **lst)
{
    if (lst && *lst)
    {
        t_list *last = ft_lstlast(*lst);
        t_list *node = *lst;

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

int find_closest_collectable(char **map, t_coord current_pos, t_legend leg, int *collected)
{
	int i;
	int shortest_dist;
	int dist;
	int closest_collectable;
	shortest_dist = INT_MAX;
	i = 0;
	while(i < leg.c_count)
	{
		if(current_pos.x == leg.c[i].x && current_pos.y == leg.c[i].y)
			(*collected)++;
		if (map[leg.c[i].y][leg.c[i].x] != 'T')
		{
			dist = abs(current_pos.x - leg.c[i].x) + abs(current_pos.y - leg.c[i].y);
			if(dist < shortest_dist)
			{
				shortest_dist = dist;
				closest_collectable = i;
			}
		}
		i++;
	}
	
	return (closest_collectable);

}
void free_map(char **map, int rows) {
	for (int i = 0; i < rows; i++) {
		free(map[i]);
	}
	free(map);
}

t_coord get_neighbors(char **map, t_coord current_pos, t_legend leg)
{
	int i;
	
	t_coord directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	t_coord next_pos;
	t_coord chosen_pos;
	static int collected;
	
	next_pos.x = 0;
	next_pos.y = 0;
	chosen_pos.x = -1;
	chosen_pos.y = -1;
	int shortest_dist;
	int neighbor_dist;
	shortest_dist = INT_MAX;
	int j;
	i=0;
	if(collected < leg.c_count)
		j = find_closest_collectable(map, current_pos, leg, &collected);
	while(i < 4)
	{
		next_pos.x = current_pos.x + directions[i].x;
		next_pos.y = current_pos.y + directions[i].y;
		if(next_pos.x < 0 || next_pos.x >= leg.col || next_pos.y < 0 || next_pos.y >= leg.row)
		{
			i++;
			continue;
		}
		if(map[next_pos.y][next_pos.x] == 'F' || map[next_pos.y][next_pos.x] == 'E' || map[next_pos.y][next_pos.x] == 'T')
		{
			if(collected == leg.c_count)
			{
				neighbor_dist = abs(next_pos.x - leg.e.x) + abs(next_pos.y - leg.e.y);
			}
			else
			{
				neighbor_dist = abs(next_pos.x - leg.c[j].x) + abs(next_pos.y - leg.c[j].y);
			}
			
			if(neighbor_dist < shortest_dist)
			{
				shortest_dist = neighbor_dist;
				chosen_pos = next_pos;
			}
		}
		i++;
	}
	return (chosen_pos);
}


int greedy_best_search(char **map, t_legend leg)
{
	//unsigned int dist = abs(leg.p.x - leg.e.x) + abs(leg.p.y - leg.e.y);
	t_coord current_pos;
	int steps;
	steps=0;
	current_pos = leg.p;
	t_coord *pos_copy = malloc(sizeof(t_coord));
    *pos_copy = current_pos;
	map[current_pos.y][current_pos.x] = 'T';
	t_list *queue = ft_lstnew(pos_copy);
	while(queue)
	{
		current_pos = get_neighbors(map, current_pos, leg);
		if(current_pos.x == -1 && current_pos.y == -1 && queue)
		{
			t_coord *pos_copy = ft_lstlast(queue)->content;
			current_pos = *pos_copy;
			free(pos_copy); 
			lstremove_back(&queue);
			steps--;
		}
		else if(map[current_pos.y][current_pos.x] == 'E')
		{
			//printf("number of steps %i\n", steps);
			//print_map(map, leg.row, leg.col);
			
			ft_lstclear(&queue, free);
			return (steps);
		}
		else
		{
			map[current_pos.y][current_pos.x] = 'T';
    		t_coord *pos_copy = malloc(sizeof(t_coord));
    		*pos_copy = current_pos;
		    ft_lstadd_back(&queue, ft_lstnew(pos_copy));
		}
		steps++;
	}
	ft_lstclear(&queue, free);
	return (0);
}

int map_isvalidpath(char **map, t_legend leg, t_vars *vars)
{
	int i;
	i = 0;
	char **path_map;
	path_map = malloc(sizeof(char *) * leg.row);
	while(i < leg.row)
	{
		path_map[i] = malloc(sizeof(char) * leg.col);
		i++;
	}
	i = 0;
	while(i < leg.row)
	{
		int j = 0;
		while(j < leg.col)
		{
			if(map[i][j] == '1')
				path_map[i][j] = 'N';
			else if(map[i][j] == 'E')
				path_map[i][j] = 'E';
			else
				path_map[i][j] = 'F';
			j++;
		}
		i++;
	}
	
	// if (leg.rows < 1 || !map || !map[0]) {
    //     return 0; // Invalid input
    // }
	int steps;
	steps = greedy_best_search(path_map, leg);
	vars->par = steps;
	free_map(path_map, leg.row);	
	return (steps);
		
	
}

int has_walls(char **map, t_legend leg)
{
	int i;
	i = 0;
	while(i < leg.col)
	{
		if(map[0][i] != '1' || map[leg.row - 1][i] != '1')
			return (0);
		if(i < leg.row)
		{
			if(map[i][0] != '1' || map[i][leg.col - 1] != '1')
			return (0);
		}
		i++;
	}
	return (1);
}

int is_rectangle(char **map, t_legend leg) 
{
    size_t length;
	int i;
	i = 0;
	length = leg.col;

	while(i < leg.row)
	{
		if (ft_strlen(map[i]) != length)
			return (0);
		i++;
	}
	return (1);
}

char **read_map(char *filename, t_vars *vars)
{
	int fd;
	char **map;
	char buf;
	int row;
	int col;
	int i;
	i=0;
	
	row = 0;
	col = 0;
	map = malloc(sizeof(char *) * vars->leg.row);
	while(row < vars->leg.row)
	{
		map[row] = malloc(sizeof(char) * vars->leg.col +1);
		map[row][vars->leg.col] = '\0';
		row++;
	}
	vars->leg.c = malloc(sizeof(t_coord) * vars->leg.c_count);
	row = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	
	while (read(fd, &buf, 1) > 0)
	{
		if(buf == '\n')
		{
			
			row++;
			col = 0;
		}
		else
		{
			if(buf == 'P')
			{
				vars->leg.p.x = col;
				vars->leg.p.y = row;
			}
			if(buf == 'E')
			{
				vars->leg.e.x = col;
				vars->leg.e.y = row;
			}
			if(buf == 'C')
			{
				vars->leg.c[i].x = col;
				vars->leg.c[i].y = row;
				i++;
			}
			map[row][col] = buf;
			col++;
		}
	}
	close(fd);
	if(!has_walls(map, vars->leg))
	{
		printf("map has no walls Error\n");
		exit (0);
	}
	if(!is_rectangle(map, vars->leg))
	{
		printf("map is not a rectangle Error\n");
		exit (0);
	}
	if(!map_isvalidpath(map, vars->leg, vars))
	{
		printf("map valid Error\n");
		exit (0);
	}
	
	printf("map is valid\n");
	
	return (map);
}





int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("wrong number of arguments Error\n");
		exit (0);
	}
	
	t_vars vars;
	
	vars = init(argv[1]);
	mlx_hook(vars.win, 2, 1L<<0, move_charachter, &vars);
	mlx_hook(vars.win, 17, 1L<<17, close_window, &vars);
	mlx_loop_hook(vars.mlx, draw_next_frame, &vars);
	mlx_loop(vars.mlx);
}




// int	main(void)
// {
	
// 	t_vars vars;
// 	vars.leg = check_map("map.ber");
// 	vars.map = read_map("map.ber", &vars);
// 	vars.x = vars.leg.p.x *16;
// 	vars.y = vars.leg.p.y * 16;
// 	printf("vars.x: %d\n", vars.x);
// 	printf("vars.y: %d\n", vars.y);
// 	printf("vars.leg.p.x: %d\n", vars.leg.p.x);
// 	printf("vars.leg.p.y: %d\n", vars.leg.p.y);
	
	
	
// 	//print_map(vars.map, vars.leg.row, vars.leg.col);
// }
	

