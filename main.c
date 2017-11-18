/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:09:23 by qhonore           #+#    #+#             */
/*   Updated: 2017/11/18 22:01:32 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "include/malloc.h"
 #include <time.h>

void	test_tiny_size_limits()
{
	char* ptr = malloc(256);

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
		ptr = malloc(256);
		if (i == 0)
			block = (t_block*)(ptr - (sizeof(t_block)));
		i++;
	}
	ptr = malloc(89);
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

	ptr = malloc(30000);
	block = (t_block*)(ptr - (sizeof(t_block)));
	ptr = malloc(2695);

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

	ptr = malloc(19);
	ptr = malloc(568);
	ptr = malloc(200);
	ptr = malloc(803);
	ptr = malloc(1925);
	ptr = malloc(3054);
	ptr = malloc(765);
	ptr = malloc(956324);
	show_alloc_mem();
}

void	test_free()
{
	void	*ptr[8];

	ptr[0] = malloc(59);
	ptr[1] = malloc(568);
	ptr[2] = malloc(200);
	ptr[3] = malloc(803);
	ptr[4] = malloc(1925);
	ptr[5] = malloc(3054);
	ptr[6] = malloc(765);
	ptr[7] = malloc(956324);
	show_alloc_mem();
	printf("=== Test free valids ptr ===\n");
	free(ptr[3]);
	free(ptr[0]);
	printf("=== Test free null ptr ===\n");
	free(0);
	printf("=== Test free invalid ptr ===\n");
	free((void*)95946546553);
	printf("=== New malloc on freed blocks ===\n");
	ptr[3] = malloc(803);
	ptr[0] = malloc(16);
	show_alloc_mem();
	show_zone_state(2);
}

void	test_malloc_0()
{
	void	*ptr;

	printf("=== TEST MALLOC 0 ===\n");
	printf("=== Malloc ptr ===\n");
	ptr = malloc(0);
	show_alloc_mem();
	printf("=== Free ptr ===\n");
	free(ptr);
	show_alloc_mem();
}

void	test_realloc()
{
	void	*ptr = NULL;

	printf("=== TEST REALLOC ===\n");
	printf("ptr = realloc(15)\n");
	ptr = realloc(ptr, 15);
	show_alloc_mem();
}

void	interactive_test()
{
	int		i = 0, j = 0, k, ret;
	char	buf;
	char	str[256];
	int	size;
	void	*ptr[256];

	while ((ret = read(0, &buf, 1)) > 0)
	{
		if (buf == '\n')
		{
			str[i] = '\0';
			if (str[0] == 'm')//malloc
			{
				size = atoi(&str[2]);
				ptr[j++] = malloc(size);
			}
			if (str[0] == 'f')//free
			{
				free(ptr[atoi(&str[2])]);
			}
			if (str[0] == 'r')//realloc
			{
				size = atoi(&str[2]);
				k = 2;
				while (str[k] != ' ')
					k++;
				k = atoi(&str[k + 1]);
				if (k == -1)
					ptr[j++] = realloc(0, size);
				else
					ptr[k] = realloc(ptr[k], size);
			}
			k = 0;
			printf("==| PTR LIST |==\n");
			while (k < j)
			{
				printf("ptr[%d] = %p\n", k, ptr[k]);
				k++;
			}
			printf("==| SHOW_ALLOC_MEM |==\n");
			show_alloc_mem();
			i = 0;
		}
		else
			str[i++] = buf;
	}
}

void	big_malloc_realloc_test()
{
	int		i;
	void	*ptr[512];
	int		m_size[512];
	int		size;

	i = 0;
	printf("=============== Malloc ptr ===============\n");
	while (i < 512)
	{
		size = rand() % 1024;
		m_size[i] = size;
		printf("====== %d: malloc(%d) ======\n", i, size);
		ptr[i] = malloc(size);
		i++;
	}
	i = 0;
	printf("=============== Free ptr ===============\n");
	while (i < 512)
	{
		size = rand() % 4;
		if (size == 0)
		{
			printf("====== %d: free(%p) ======\n", i, ptr[i]);
			free(ptr[i]);
		}
		i++;
	}
	i = 0;
	printf("=============== Realloc ptr ===============\n");
	while (i < 512)
	{
		size = rand() % 1024;
		printf("====== %d: realloc(%d) -> malloc(%d) ======\n", i, size, m_size[i]);
		ptr[i] = realloc(ptr[i], size);
		i++;
	}
	show_alloc_mem();
}

int		main(int ac, char **av)
{
	srand(time(NULL));
	// test_tiny_size_limits();
	// test_tiny_create_extra_zone();
	// test_large_malloc();
	// test_show_alloc_mem();
	// test_free();
	// test_malloc_0();
	// test_realloc();
	// interactive_test();
	// big_malloc_realloc_test();
	char *ptr = malloc(100);
	int i;
	memset(ptr, '6', 100);
	i = -1;
	while (++i < 100)
		printf("ptr[%d] = %d\n", i, ptr[i]);
	sfree(ptr, 0);
	printf("sfree (ptr, '0')\n");
	i = -1;
	while (++i < 100)
		printf("ptr[%d] = %d\n", i, ptr[i]);
	return (0);
}
