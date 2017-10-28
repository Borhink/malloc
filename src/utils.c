/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:03:21 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/28 18:54:18 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_env	*get_env(void)
{
	static t_env	e = {NULL, 0, NULL, 0, NULL};

	return (&e);
}

int		is_next_same_zone(t_block *block)
{
	if ((void*)block + sizeof(t_block) + block->size == block->next)
		return (1);
	return (0);
}

void	create_block(t_block *block, size_t size)
{
	t_block		*tmp;

	block->free = 0;
	if (block->size != size)
	{
		tmp = block->next;
		if (tmp && tmp->free && is_next_same_zone(block))
		{
			block->next = (t_block*)((void*)block + sizeof(t_block) + size);
			block->next->free = 1;
			block->next->size = block->size - size + tmp->size;
			block->next->next = tmp->next;
			block->size = size;
		}
		else if (block->size - size > sizeof(t_block))
		{
			block->next = (t_block*)((void*)block + sizeof(t_block) + size);
			block->next->free = 1;
			block->next->size = block->size - size - sizeof(t_block);
			block->next->next = tmp;
			block->size = size;
		}
	}
}

int		get_size_type(size_t size)
{
	if (size > SIZE_SMALL)
		return (TYPE_LARGE);
	if (size > SIZE_TINY)
		return (TYPE_SMALL);
	return (TYPE_TINY);
}

t_block	*find_block(t_block *block, void *ptr)
{
	while (block)
	{
		if ((void*)block + sizeof(t_block) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

void	merge_next_block(t_block *block)
{
	t_block	*tmp;

	tmp = block->next;
	if (tmp && tmp->free && is_next_same_zone(block))
	{
		block->next = tmp->next;
		block->size += tmp->size + sizeof(t_block);
	}
}
