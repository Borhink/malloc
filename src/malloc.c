/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:43:33 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/21 19:14:29 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	create_block(t_block *block, size_t size)
{
	t_block		*tmp;

	block->free = 0;
	if (block->size != size)
	{
		tmp = block->next;
		block->next = block + sizeof(t_block) + size;
		block->next->free = 1;
		block->next->size = block->size - size - sizeof(t_block);
		block->next->next = tmp;
		block->size = size;
	}
}

void	*tiny_malloc(t_env *env, size_t size)
{
	t_block		*block;

	block = env->tiny;
	while (block)
	{
		if (block->free && block->size >= size)
		{
			create_block(block, size);
			return (block + sizeof(t_block));
		}
		block = block->next;
	}
	return (NULL);
}

void	*ft_malloc(size_t size)
{
	static t_env	env = {NULL, 0, NULL, 0, NULL};

	if (env.tiny == NULL && !init_zones(&env))
		return (NULL);
	if (size > SMALL)
		return (NULL);//LARGE
	else if (size > TINY)
		return (NULL);//SMALL
	else
		return (tiny_malloc(&env, size));
}
