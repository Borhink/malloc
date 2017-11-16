/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:54:55 by qhonore           #+#    #+#             */
/*   Updated: 2017/11/16 19:12:48 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*get_block_ptr(t_env *e, void *ptr, int *type)
{
	t_block	*block;

	if ((block = find_block(e->tiny, ptr)))
		*type = TYPE_TINY;
	else if ((block = find_block(e->small, ptr)))
		*type = TYPE_SMALL;
	else if ((block = find_block(e->large, ptr)))
		*type = TYPE_LARGE;
	else
		return (NULL);
	return (block);
}

void	*new_alloc(t_block *block, size_t size)
{
	void	*ptr;

	if ((ptr = (void*)malloc(size)))
	{
		if (size > block->size)
			ft_memcpy(ptr, (void*)block + sizeof(t_block), block->size);
		else
			ft_memcpy(ptr, (void*)block + sizeof(t_block), size);
		free((void*)block + sizeof(t_block));
		return (ptr);
	}
	else
		return (NULL);
}

void	*same_alloc_type(t_block *block, size_t size)
{
	if ((size < block->size) ||
	(block->next && block->next->free && is_next_same_zone(block)
	&& block->next->size + block->size >= size))
	{
		create_block(block, size);
		return ((void*)block + sizeof(t_block));
	}
	else if (block->next && block->next->free && is_next_same_zone(block)
	&& block->next->size + block->size + sizeof(t_block) >= size)
	{
		merge_next_block(block);
		return ((void*)block + sizeof(t_block));
	}
	else
		return (new_alloc(block, size));
}

void	*realloc(void *ptr, size_t size)
{
	t_env	*e;
	t_block	*block;
	int		cur_type;
	int		new_type;

	e = get_env();
	if (!ptr)
		return (malloc(size));
	if (!(block = get_block_ptr(e, ptr, &cur_type)))
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (size == block->size)
		return (ptr);
	else
	{
		if ((new_type = get_size_type(size)) == cur_type)
			return (same_alloc_type(block, size));
		else
			return (new_alloc(block, size));
	}
}
