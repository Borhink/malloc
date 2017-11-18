/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:42:24 by qhonore           #+#    #+#             */
/*   Updated: 2017/11/18 21:18:37 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	merge_all_free(t_block *block)
{
	int		ret;

	while (block)
	{
		ret = 0;
		if (block->free)
			ret = merge_next_block(block);
		if (ret == 0)
			block = block->next;
	}
}

static int	free_ptr(t_block *block, void *ptr, int set_mem, char val)
{
	t_block		*start;

	start = block;
	while (block)
	{
		if ((void*)block + sizeof(t_block) == ptr)
		{
			if (block->free == 1)
				return (1);
			block->free = 1;
			if (set_mem)
				ft_memset((void*)block + sizeof(t_block), val, block->size);
			merge_all_free(start);
			return (1);
		}
		block = block->next;
	}
	return (0);
}

void		free(void *ptr)
{
	t_env	*e;

	e = get_env();
	if (!ptr)
		return ;
	if (free_ptr(e->tiny, ptr, 0, 0) || free_ptr(e->small, ptr, 0, 0)
	|| free_ptr(e->large, ptr, 0, 0))
		return ;
}

void		sfree(void *ptr, char val)
{
	t_env	*e;

	e = get_env();
	if (!ptr)
		return ;
	if (free_ptr(e->tiny, ptr, 1, val) || free_ptr(e->small, ptr, 1, val)
	|| free_ptr(e->large, ptr, 1, val))
		return ;
}
