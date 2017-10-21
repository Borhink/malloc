/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 13:53:36 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/21 17:53:18 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_block(t_block *block, int size, t_block *next, int free)
{
	block->size = size - sizeof(t_block);
	block->next = next;
	block->free = free;
}

int		create_zone(t_env *env, int type)
{
	const int	size = (type == TYPE_TINY ? env->tiny_size : env->small_size);
	t_block		**block;
	t_block		*tmp;

	block = (type == TYPE_TINY ? &env->tiny : &env->small);
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

int		init_zones(t_env *env)
{
	const int	page_size = getpagesize();

	env->tiny_size = (TINY * 100 - 1) / page_size * page_size + page_size;
	env->small_size = (SMALL * 100 - 1) / page_size * page_size + page_size;
	if (!create_zone(env, TYPE_TINY) || !create_zone(env, TYPE_SMALL))
		return (0);
	return (1);
}
