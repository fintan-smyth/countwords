/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:06 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/20 14:46:09 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_tree_new(void *content)
{
	t_tree	*new;

	new = ft_calloc(1, sizeof(*new));
	new->content = content;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	ft_free_treenode(t_tree *node, void (*del)(void *))
{
	if (del != NULL)
		del(node->content);
	free(node);
}

void	ft_traverse_tree(t_tree *tree, int order,
			void (*f)(t_tree *, void *), void *data)
{
	if (tree == NULL)
		return ;
	if (order == PRE_ORD)
		f(tree, data);
	ft_traverse_tree(tree->left, order, f, data);
	if (order == IN_ORD)
		f(tree, data);
	ft_traverse_tree(tree->right, order, f, data);
	if (order == PST_ORD)
		f(tree, data);
}

void	ft_tree_clear(t_tree *tree, void (*del)(void *))
{
	ft_traverse_tree(tree, PST_ORD,
		(void (*)(t_tree *, void *))ft_free_treenode, del);
}
