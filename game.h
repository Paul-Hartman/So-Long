/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:41:44 by phartman          #+#    #+#             */
/*   Updated: 2024/05/27 17:10:58 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <X11/Xlib.h>
#include "libft/libft.h"
#include <stdio.h>


# define KEY_UP 65362
# define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	t_data	img;
}				t_vars;

