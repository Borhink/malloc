/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 13:53:36 by qhonore           #+#    #+#             */
/*   Updated: 2017/11/16 19:43:45 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_env	*get_env(void)
{
	static t_env	e = {NULL, 0, NULL, 0, NULL, PTHREAD_MUTEX_INITIALIZER};

	return (&e);
}

void	create_block(t_block *block, size_t size)
{
	t_block	tmp;
	t_block	*next;

	block->free = 0;
	if (block->size == size)
		return ;
	if (block->next)
		tmp = *(block->next);
	next = block->next;
	if (block->next && block->next->free && is_next_same_zone(block))
	{
		block->next = (t_block*)((void*)block + sizeof(t_block) + size);
		block->next->free = 1;
		block->next->size = (int)block->size - (int)size + tmp.size;
		block->next->next = tmp.next;
		block->size = size;
	}
	else if ((int)block->size - (int)size > (int)sizeof(t_block))
	{
		block->next = (t_block*)((void*)block + sizeof(t_block) + size);
		block->next->free = 1;
		block->next->size = (int)block->size - (int)size - sizeof(t_block);
		block->next->next = next;
		block->size = size;
	}
}

void	init_block(t_block *block, int size, t_block *next, int free)
{
	block->size = size - sizeof(t_block);
	block->next = next;
	block->free = free;
}

int		create_zone(t_block **block, size_t size)
{
	t_block		*tmp;

	if (*block == NULL)
	{
		if ((*block = (void*)mmap(NULL, size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			return (0);
		init_block(*block, size, NULL, 1);
	}
	else
	{
		tmp = *block;
		while (tmp->next)
			tmp = tmp->next;
		if ((tmp->next = (void*)mmap(NULL, size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			return (0);
		init_block(tmp->next, size, NULL, 1);
	}
	return (1);
}

int		init_zone(t_env *e, int type)
{
	if (type == TYPE_TINY)
	{
		e->tiny_size = ALIGN_PAGE((SIZE_TINY + sizeof(t_block)) * 100);
		if (!create_zone(&e->tiny, e->tiny_size))
			return (0);
	}
	else
	{
		e->small_size = ALIGN_PAGE((SIZE_SMALL + sizeof(t_block)) * 100);
		if (!create_zone(&e->small, e->small_size))
			return (0);
	}
	return (1);
}
