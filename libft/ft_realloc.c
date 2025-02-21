/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:53:16 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/21 14:07:53 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*out;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	out = malloc(new_size);
	if (new_size < old_size)
		ft_memmove(out, ptr, new_size);
	else
		ft_memmove(out, ptr, old_size);
	free(ptr);
	return (out);
}

void	*ft_recalloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*out;

	if (ptr == NULL)
		return (ft_calloc(1, new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	out = ft_calloc(1, new_size);
	if (new_size < old_size)
		ft_memmove(out, ptr, new_size);
	else
		ft_memmove(out, ptr, old_size);
	free(ptr);
	return (out);
}
