/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:42:24 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/25 18:01:51 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		find_ptr(t_block *block, void *ptr)
{
	while (block)
	{
		if ((void*)block + sizeof(t_block) == ptr)
		{
			//if (block->free == 1) DEJA FREE
			block->free = 1;
			return (1);
		}
		block = block->next;
	}
	return (0);
}

void	my_free(void *ptr)
{
	t_env	*e;

	e = get_env();
	if (!ptr)
		return ;
	if (find_ptr(e->tiny, ptr) || find_ptr(e->small, ptr)
	|| find_ptr(e->large, ptr))
	{
		ft_printf("Ptr %p is now free()\n", ptr);
		//ok
	}
	else
	{
		ft_printf("Ptr %p not found\n", ptr);
		//pas trouvé
	}
}
