/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 13:53:36 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/24 11:04:55 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

int		init_zones(t_env *e)
{
	const int	page = getpagesize();

	e->tiny_size = ((TINY + sizeof(t_block)) * 100 - 1) / page * page + page;
	e->small_size = ((SMALL + sizeof(t_block)) * 100 - 1) / page * page + page;
	if (!create_zone(&e->tiny, e->tiny_size)
	|| !create_zone(&e->small, e->small_size))
		return (0);
	return (1);
}
