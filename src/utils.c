/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:03:21 by qhonore           #+#    #+#             */
/*   Updated: 2017/11/16 19:36:35 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		is_next_same_zone(t_block *block)
{
	if ((void*)block + sizeof(t_block) + block->size == block->next)
		return (1);
	return (0);
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
		if ((void*)block + sizeof(t_block) == ptr && !(block->free))
			return (block);
		block = block->next;
	}
	return (NULL);
}

int		merge_next_block(t_block *block)
{
	t_block	tmp;

	if (block->next && block->next->free && is_next_same_zone(block))
	{
		tmp = *(block->next);
		block->next = tmp.next;
		block->size += tmp.size + sizeof(t_block);
		return (1);
	}
	return (0);
}

void	print_block(t_block *block, void *ptr)
{
	ft_putstr("struct block (addr: ");
	print_unsigned((unsigned long)block, 16, 1);
	ft_putstr(") (ptr: ");
	print_unsigned((unsigned long)ptr, 16, 1);
	ft_putstr(") { free: ");
	print_unsigned(block->free, 10, 0);
	ft_putstr(", size: ");
	print_unsigned(block->size, 10, 0);
	ft_putstr(", next: ");
	print_unsigned((unsigned long)block->next, 16, 1);
	ft_putstr(" };\n");
}
