/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 16:36:16 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/20 17:25:44 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc/malloc.h>

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new;
	size_t	cur_size;

	if (!ptr && new_size)
		return (malloc(new_size));
	else if (!new_size && ptr)
		free(ptr);
	else if (ptr && new_size)
	{
		if (!(new = (void*)malloc(new_size)))
			return (ptr);
		cur_size = malloc_size(ptr);
		if (cur_size <= new_size)
			ft_memcpy(new, ptr, cur_size);
		else
			ft_memcpy(new, ptr, new_size);
		free(ptr);
		return (new);
	}
	return (NULL);
}
