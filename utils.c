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


int	get_dist(t_coord a, t_coord b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

void	print_error(char *error_msg)
{
	perror(error_msg);
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