/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:54:55 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/26 19:27:39 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*find_block(t_block *block, void *ptr)
{
	while (block)
	{
		if ((void*)block + sizeof(t_block) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

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

int		get_size_type(size_t size)
{
	if (size > SIZE_SMALL)
		return (TYPE_LARGE);
	if (size > SIZE_TINY)
		return (TYPE_SMALL);
	return (TYPE_TINY);
}

void	*same_type_alloc(t_env *e, t_block *block, size_t size)
{
	t_block	*tmp;
	size_t	free_size;

	if (size < block->size)
	{
		create_block(block, size);//check si le block suivant est free
		return ((void*)block + sizeof(t_block));
	}
	if (block->next && block->next->free
	&& block->next->size + block->size + sizeof(t_block) >= size)

	}
	tmp = block->next;
	free_size = block->size;
	while (tmp)
	{
		free_size += block->size
		if ()
		tmp = tmp->next;
	}
}

24:12|24:8
realloc 8 ->  24:8|24:12 //plus petit + next->free
realloc 13 -> 24:13|24:7 //plus grand + next->free assez grand
realloc 20 -> 24:20|24:0 //plus grand + next->free assez grand
realloc 21 -> 24:44|0    //plus grand + next->free assez grand, mais trop petit pour split
realloc 88 -> //plus grand + pas assez de place, nouvelle alloc

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
		{/* alloc nouveau dans le bon type + copie + free */}
	}
}

// Si ptr = NULL, return new malloc						OK
// Si ptr KO -> return NULL								OK
// Si ptr OK et size = 0 -> free ptr + return NULL		OK

// Si ptr Ok et size OK -> resize alloc
