/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:43:33 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/25 18:00:32 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*tiny_small_alloc(t_env *e, size_t size, int type)
{
	t_block		*block;

	block = (type == TYPE_TINY ? e->tiny : e->small);
	while (block)
	{
		if (block->free && block->size >= size)
		{
			create_block(block, size);
			return ((void*)block + sizeof(t_block));
		}
		block = block->next;
	}
	if ((type == TYPE_TINY && !create_zone(&e->tiny, e->tiny_size))
	|| (type == TYPE_SMALL && !create_zone(&e->small, e->small_size)))
		return (NULL);
	else
		return (tiny_small_alloc(e, size, type));
}

void	*large_alloc(t_env *e, size_t size)
{
	t_block		*block;

	block = e->large;
	while (block)
	{
		if (block->free && block->size >= size)
		{
			create_block(block, size);
			return ((void*)block + sizeof(t_block));
		}
		block = block->next;
	}
	if (!create_zone(&e->large, ALIGN_PAGE(size + sizeof(t_block))))
		return (NULL);
	else
		return (large_alloc(e, size));
}

void	*ft_malloc(size_t size)
{
	t_env	*e;

	e = get_env();
	if (size > SMALL)
		return (large_alloc(e, size));
	else if (size > TINY)
	{
		if (e->small == NULL && !init_zone(e, TYPE_SMALL))
			return (NULL);
		return (tiny_small_alloc(e, size, TYPE_SMALL));
	}
	else
	{
		if (e->tiny == NULL && !init_zone(e, TYPE_TINY))
			return (NULL);
		return (tiny_small_alloc(e, size, TYPE_TINY));
	}
}
