/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:42:24 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/31 16:45:38 by qhonore          ###   ########.fr       */
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

static int	free_ptr(t_block *block, void *ptr)
{
	t_block		*start;

	start = block;
	while (block)
	{
		if ((void*)block + sizeof(t_block) == ptr)
		{
			// if (block->free == 1) DEJA FREE
			block->free = 1;
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
	if (free_ptr(e->tiny, ptr) || free_ptr(e->small, ptr)
	|| free_ptr(e->large, ptr))
	{
		//ok
	}
	else
	{
		//pas trouvé
	}
}
