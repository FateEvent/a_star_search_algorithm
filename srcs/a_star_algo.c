/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:00:02 by faventur          #+#    #+#             */
/*   Updated: 2022/08/15 16:00:02 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a_star.h"

t_tile	*tile_init()
{
	t_tile	*tile;

	tile = (t_tile *)malloc(sizeof(t_tile));
	memset(tile,'\0', sizeof(*tile));
	tile->x = 0;
	tile->y = 0;
	tile->cost = 0;
	tile->distance = 0;
	tile->cost_distance = 0;
	tile->parent = NULL;
	return (tile);
}

void	set_distance(t_tile *tile, int target_x, int target_y)
{
	tile->distance = abs(target_x - tile->x) + abs(target_y - tile->y);
}

void	set_cost_distance(t_tile *tile)
{
	tile->cost_distance = tile->cost + tile->distance;
}

void	find_coordinates(t_tile *tile, char *map[], char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				tile->y = i;
				tile->x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_max_y(char *map[])
{
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_max_x(char *map[])
{
	size_t	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

t_tile	*tile_creator(int x, int y, t_tile *parent, int cost)
{
	t_tile	*tile;

	tile = tile_init();
	tile->x = x;
	tile->y = y;
	tile->cost = cost;
	tile->parent = parent;
	return (tile);
}

void	tile_display(t_tile *tile)
{
	printf("x: %d\ny: %d\ncost: %d\n", tile->x, tile->y, tile->cost);
	printf("distance: %d\ncost_distance: %d\n", tile->distance, tile->cost_distance);
	if (tile->parent)
		printf("parent's x: %d\nparent's y: %d\n", tile->parent->x, tile->parent->y);
}

void	ft_tiledischarge(t_stack *stack, t_node *node)
{
	if (!node || !stack)
		return ;
	if (node->next == NULL)
	{
		stack->bottom = node->prev;
		if (stack->bottom)
			stack->bottom->next = NULL;
	}
	else if (node->prev == NULL)
	{
		stack->top = node->next;
		if (stack->top)
			stack->top->prev = NULL;
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
}

void	ft_tiledel(t_tile *tile)
{
	if (tile)
	{
		free(tile->parent);
		tile->parent = NULL;
		free(tile);
		tile = NULL;
	}
}

int	ft_check_conditions(t_tile *current, char *map[])
{
	int	max_x;
	int	max_y;

	max_x = ft_max_x(map) - 1;
	max_y = ft_max_y(map) - 1;
	if ((current->x >= 0 && current->x <= max_x)
		&& (current->y >= 0 && current->y <= max_y)
		&& (map[current->y][current->x] == ' '
		|| map[current->y][current->x] == 'B'))
		return (0);
	return (1);
}

t_stack	*get_walkable_tiles(char *map[], t_tile *current, t_tile *target)
{
	t_stack	*possible_tiles;
	t_node	*tmp;

	possible_tiles = ft_stacknew();
	ft_stackadd_bottom(possible_tiles, ft_newnode(tile_creator(current->x,
		current->y - 1, current, current->cost + 1)));
	ft_stackadd_bottom(possible_tiles, ft_newnode(tile_creator(current->x,
		current->y + 1, current, current->cost + 1)));
	ft_stackadd_bottom(possible_tiles, ft_newnode(tile_creator(current->x - 1,
		current->y, current, current->cost + 1)));
	ft_stackadd_bottom(possible_tiles, ft_newnode(tile_creator(current->x + 1,
		current->y, current, current->cost + 1)));
	tmp = possible_tiles->top;
	while (tmp)
	{
		set_distance(tmp->content, target->x, target->y);
		set_cost_distance(tmp->content);
		if (ft_check_conditions(tmp->content, map))
			ft_tiledischarge(possible_tiles, tmp);
		tmp = tmp->next;
	}
	return (possible_tiles);
}

int	ft_tiles_compare(t_tile *a, t_tile *b)
{
	return (a->cost_distance - b->cost_distance);
}

int	ft_tiles_equal(t_tile *a, t_tile *b)
{
	if (a->x == b->x && a->y == b->y)
		return (1);
	return (0);
}

int	ft_stack_any(t_stack *stack, t_node *walkable, int (*f)())
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		if (f(current->content, walkable->content))
			return (1);
		current = current->next;
	}
	return (0);
}

t_node	*ft_stack_first(t_stack *stack, t_node *walkable, int (*f)())
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		if (f(current->content, walkable->content))
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	main(void)
{
	t_stack	*active_tiles;
	t_stack	*visited_tiles;
	t_stack	*walkable_tiles;
	t_node	*walkable;
	t_node	*check_tile;
	t_node	*existing_tile;
	t_tile	*start;
	t_tile	*finish;
	char	*map[] = {
		"A          ",
		"--| |------",
		"           ",
		"   |-----| ",
		"   |     | ",
		"---|     |B"
	};

	start = tile_init();
	find_coordinates(start, map, 'A');
	finish = tile_init();
	find_coordinates(finish, map, 'B');
	set_distance(start, finish->x, finish->y);
	active_tiles = ft_stacknew();
	visited_tiles = ft_stacknew();
	ft_stackadd_bottom(active_tiles, ft_newnode(start));
	while(ft_stacksize(active_tiles))
	{
		ft_stacksort(active_tiles, ft_tiles_compare);
		check_tile = active_tiles->top;
		if (ft_tiles_equal(check_tile->content, finish))
		{
			printf("We are at the destination!\n");
			//We can actually loop through the parents of each tile to find our exact path which we will show shortly. 
			return (0);
		}
		ft_stackadd_bottom(visited_tiles, check_tile);
		ft_tiledischarge(active_tiles, check_tile);
		walkable_tiles = get_walkable_tiles(map, check_tile->content, finish);
		walkable = walkable_tiles->top;
		while (walkable)
		{
			printf("Walkabilly!\n");
			tile_display(walkable->content);
			//We have already visited this tile so we don't need to do so again!
			if (ft_stack_any(visited_tiles, walkable, ft_tiles_equal))
				continue ;
			printf("miao!\n");
			//It's already in the active list, but that's OK, maybe this new tile has a better value (e.g. We might zigzag earlier but this is now straighter). 
			if (ft_stack_any(active_tiles, walkable, ft_tiles_equal))
			{
				printf("bao!\n");
				existing_tile = ft_stack_first(active_tiles, walkable, ft_tiles_equal);
				if (ft_tiles_compare(existing_tile->content, check_tile->content) > 0)
				{
					ft_tiledischarge(active_tiles, existing_tile);
					ft_stackadd_bottom(active_tiles, walkable);
				}
			}
			else
			{
				printf("gnao!\n");
				//We've never seen this tile before so add it to the list. 
				ft_stackadd_bottom(active_tiles, walkable->content);
			}
			walkable = walkable->next;
			printf("rao!\n");
		}
	}
	printf("No Path Found!\n");
}
