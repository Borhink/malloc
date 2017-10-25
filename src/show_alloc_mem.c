/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:09:39 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/25 17:19:32 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int show_zone(t_block *block)
{
	int		i;
	void	*ptr;

	i = 0;
	while (block)
	{
		if (!block->free)
		{
			ptr = (void*)block + sizeof(t_block);
			if (block->size > 1)
				ft_printf("%p - %p : %d octets\n", ptr, ptr + block->size,\
				block->size);
			else
				ft_printf("%p - %p : %d octet\n", ptr, ptr + block->size,\
				block->size);
			i += block->size;
		}
		block = block->next;
	}
	return (i);
}

void		show_alloc_mem(void)
{
	const t_env	*e = get_env();
	int			size;

	ft_printf("TINY : %p\n", e->tiny);
	size = show_zone(e->tiny);
	ft_printf("SMALL : %p\n", e->small);
	size += show_zone(e->small);
	ft_printf("LARGE : %p\n", e->large);
	size += show_zone(e->large);
	if (size > 1)
		ft_printf("Total : %d octets\n", size);
	else
		ft_printf("Total : %d octet\n", size);
}
