/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:10:47 by faventur          #+#    #+#             */
/*   Updated: 2022/07/22 21:21:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QTREES_H
# define QTREES_H

# include <stdlib.h>

typedef struct s_qtree
{
	void			*item;
	struct s_node	*north;
	struct s_node	*east;
	struct s_node	*south;
	struct s_node	*west;
}					t_qtree;

t_qtree	*qtree_create_node(void *item);

//void	btree_apply_prefix(t_btree *root, void (*applyf)(void *));
//void	btree_apply_infix(t_btree *root, void (*applyf)(void *));
//void	btree_apply_suffix(t_btree *root, void (*applyf)(void *));
//void	btree_insert_data(t_btree **root, void *item, int (*cmpf)
//			(void *, void *));
//void	*btree_search_item(t_btree *root, void *data_ref, int (*cmpf)
//			(void *, void *));
//void	ft_btree_clear(t_btree *root, void (*del)(void *));
//int		btree_level_count(t_btree *root);

#endif