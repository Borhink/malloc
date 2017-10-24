/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:09:23 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/24 11:03:56 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "include/malloc.h"

void	test_tiny_size_limits()
{
	char* ptr = ft_malloc(256);

	printf("ptr: %p\n", ptr);
	ptr[0] = 1;
	printf("ptr[0]: %d\n", ptr[0]);
	ptr[28095] = 18;
	printf("ptr[28095]: %d\n", ptr[28095]);
	printf("page_size: %d\n", getpagesize());
	printf("page_size: %d, page_size * 6: %d, page_size * 7 : %d\n", getpagesize(), getpagesize() * 6, getpagesize() * 7);
	ptr[28096] = 18;
	printf("ptr[28096]: %d\n", ptr[28096]);
}

void	test_tiny_create_zone()
{
	int		i = 0;
	char	*ptr;
	t_block	*block;

	while (i < 103)
	{
		ptr = ft_malloc(256);
		if (i == 0)
			block = (t_block*)(ptr - (sizeof(t_block)));
		//printf("%03d ptr: %p\n", i, ptr);
		i++;
	}
	i = 0;
	while (block)
	{
		//printf("======== BLOCK %03d FOUND ========\n", i++);
		//printf("struct block (addr: %p)\n{\n\tfree: %d,\n\tsize: %zu,\n\tnext: %p\n};\n", block, block->free, block->size, block->next);
		block = block->next;
	}
}

int		main()
{
	//test_tiny_size_limits();
	test_tiny_create_zone();
	return (0);
}
