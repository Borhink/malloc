/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:09:23 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/25 16:13:38 by qhonore          ###   ########.fr       */
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

void	test_tiny_create_extra_zone()
{
	int		i = 0;
	char	*ptr;
	t_block	*block;

	while (i < 102)
	{
		ptr = ft_malloc(256);
		if (i == 0)
			block = (t_block*)(ptr - (sizeof(t_block)));
		i++;
	}
	ptr = ft_malloc(89);
	i = 0;
	while (block)
	{
		printf("======== BLOCK %03d FOUND ========\n", i++);
		printf("struct block (addr: %p)\n{\n\tfree: %d,\n\tsize: %zu,\n\tnext: %p\n};\n", block, block->free, block->size, block->next);
		block = block->next;
	}
}

void	test_large_malloc()
{
	int		i = 0;
	char	*ptr;
	t_block	*block;

	ptr = ft_malloc(30000);
	block = (t_block*)(ptr - (sizeof(t_block)));
	ptr = ft_malloc(2695);

	i = 0;
	while (block)
	{
		printf("======== BLOCK %03d FOUND ========\n", i++);
		printf("struct block (addr: %p)\n{\n\tfree: %d,\n\tsize: %zu,\n\tnext: %p\n};\n", block, block->free, block->size, block->next);
		block = block->next;
	}
}

void	test_show_alloc_mem()
{
	void	*ptr;

	ptr = ft_malloc(19);
	ptr = ft_malloc(568);
	ptr = ft_malloc(200);
	ptr = ft_malloc(803);
	ptr = ft_malloc(1925);
	ptr = ft_malloc(3054);
	ptr = ft_malloc(765);
	ptr = ft_malloc(956324);
	show_alloc_mem();
}

int		main()
{
	// test_tiny_size_limits();
	// test_tiny_create_extra_zone();
	// test_large_malloc();
	test_show_alloc_mem();
	return (0);
}
