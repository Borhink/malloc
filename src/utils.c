/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:03:21 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/25 13:42:03 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_env	*get_env(void)
{
	static t_env	e = {NULL, 0, NULL, 0, NULL};

	return (&e);
}

void	create_block(t_block *block, size_t size)
{
	t_block		*tmp;

	block->free = 0;
	if (block->size != size && block->size - size > sizeof(t_block))
	{
		tmp = block->next;
		block->next = (t_block*)((void*)block + sizeof(t_block) + size);
		block->next->free = 1;
		block->next->size = block->size - size - sizeof(t_block);
		block->next->next = tmp;
		block->size = size;
	}
}
