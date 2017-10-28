/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:54:55 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/28 19:22:50 by qhonore          ###   ########.fr       */
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

void	*same_type_alloc(t_env *e, t_block *block, size_t size)
{
	t_block	*tmp;
	size_t	free_size;

	if ((size < block->size) ||
	(block->next && block->next->free && is_next_same_zone(block)
	&& block->next->size + block->size >= size))
	{
		create_block(block, size);
		return ((void*)block + sizeof(t_block));
	}
	else if (block->next && block->next->free && is_next_same_zone(block)
	&& block->next->size + block->size + sizeof(t_block) >= size)
		merge_next_block(block);

}

// 24:42|24:8
// realloc 38 ->  24:38|24:12 //plus petit + next->free			OK
// realloc 43 -> 24:43|24:7 //plus grand + next->free assez grand	OK
// realloc 50 -> 24:50|24:0 //plus grand + next->free assez grand	OK
// realloc 51 -> 24:74|0    //plus grand + next->free assez grand, mais trop petit pour split OK
//
// realloc 88 -> //plus grand + pas assez de place, nouvelle alloc	TODO

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
			return (same_type_alloc(e, block, size));
		else
		{/* alloc dans le bon type + copie + free */}
	}
}

// Si ptr = NULL, return new malloc						OK
// Si ptr KO -> return NULL								OK
// Si ptr OK et size = 0 -> free ptr + return NULL		OK

// Si ptr Ok et size OK -> resize alloc
