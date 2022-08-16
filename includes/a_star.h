#ifndef _H
# define _H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "stacks.h"

typedef struct s_tile
{
	int				x;
	int				y;
	int				cost;
	int				distance;
	int				cost_distance;
	struct s_tile	*parent;
}				t_tile;

void	ft_tiledischarge(t_stack *stack, t_node *node);

#endif