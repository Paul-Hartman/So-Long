/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:34:22 by phartman          #+#    #+#             */
/*   Updated: 2024/06/12 14:52:34 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

void	print_error(char *error_msg)
{
	ft_printf("Error\n %s", error_msg);
	exit(1);
}

void	malloc_protection(void *ptr)
{
	if (ptr == NULL)
		print_error(MALLOC_ERROR);
}

t_coord	assign_coord(int x, int y)
{
	t_coord	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

int	flood_fill(char **map, t_coord pos, int row_max, int col_max)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= row_max || pos.x >= col_max
		|| map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'T')
	{
		return (0);
	}
	map[pos.y][pos.x] = 'T';
	flood_fill(map, assign_coord(pos.x, pos.y + 1), row_max, col_max);
	flood_fill(map, assign_coord(pos.x, pos.y - 1), row_max, col_max);
	flood_fill(map, assign_coord(pos.x + 1, pos.y), row_max, col_max);
	flood_fill(map, assign_coord(pos.x - 1, pos.y), row_max, col_max);
	return (0);
}
