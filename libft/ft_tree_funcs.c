/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:13:55 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/22 14:34:03 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	treecount_add(t_tree *tree, int *count)
{
	(void)tree;
	(*count)++;
}

int	ft_treesize(t_tree *tree)
{
	int	count;

	count = 0;
	ft_traverse_tree(tree, PRE_ORD,
		(void (*)(void *, void *))treecount_add, &count);
	return (count);
}

static void	ft_add_tree_arr(void *node, void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	arr[i] = ((t_tree *)node)->content;
}

void	**ft_tree_to_arr(t_tree *tree)
{
	void	**arr;

	arr = ft_calloc(ft_treesize(tree) + 1, sizeof(void *));
	ft_traverse_tree(tree, IN_ORD,
		(void (*)(void *, void *))ft_add_tree_arr, arr);
	return (arr);
}
