/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:03:21 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/31 18:34:03 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		is_next_same_zone(t_block *block)
{
	if ((void*)block + sizeof(t_block) + block->size == block->next)
		return (1);
	return (0);
}

void	create_block(t_block *block, size_t size)
{
	t_block	tmp;
	t_block	*next;

	block->free = 0;
	if (block->size != size)
	{
		ft_putstr("File ");
		ft_putstr(__FILE__);
		ft_putstr(" : ");
		ft_putnbr(__LINE__);
		ft_putstr("\n");
		if (block->next)
			tmp = *(block->next);
		next = block->next;
			ft_putstr("File ");
			ft_putstr(__FILE__);
			ft_putstr(" : ");
			ft_putnbr(__LINE__);
			ft_putstr("\n");
		if (block->next && block->next->free && is_next_same_zone(block))
		{
			ft_putstr("File ");
			ft_putstr(__FILE__);
			ft_putstr(" : ");
			ft_putnbr(__LINE__);
			ft_putstr("\n");
			block->next = (t_block*)((void*)block + sizeof(t_block) + size);
			block->next->free = 1;
			block->next->size = (int)block->size - (int)size + tmp.size;
			block->next->next = tmp.next;
			block->size = size;
				ft_putstr("File ");
				ft_putstr(__FILE__);
				ft_putstr(" : ");
				ft_putnbr(__LINE__);
				ft_putstr("\n");
		}
		else if ((int)block->size - (int)size > (int)sizeof(t_block))
		{
			ft_putstr("File ");
			ft_putstr(__FILE__);
			ft_putstr(" : ");
			ft_putnbr(__LINE__);
			ft_putstr("\n");
			block->next = (t_block*)((void*)block + sizeof(t_block) + size);
			block->next->free = 1;
			block->next->size = (int)block->size - (int)size - sizeof(t_block);
			block->next->next = next;
			block->size = size;
				ft_putstr("File ");
				ft_putstr(__FILE__);
				ft_putstr(" : ");
				ft_putnbr(__LINE__);
				ft_putstr("\n");
		}
			ft_putstr("File ");
			ft_putstr(__FILE__);
			ft_putstr(" : ");
			ft_putnbr(__LINE__);
			ft_putstr("\n");
	}
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

void	debug_pls(char *line, t_block *block)
{
	char c = 'o';

	printf("=== %s ===\n", line);
	printf("block (addr: %p) { free: %d, size: %zu, next: %p };\n", block, block->free, block->size, block->next);
	if (block->next)
		printf("block->next (addr: %p) { free: %d, size: %zu, next: %p };\n", block->next, block->next->free, block->next->size, block->next->next);
	else
		printf("block->next = NULL\n");
	while (c != '\n')
		read(0, &c, 1);
}

static int	intlen(int n)
{
	int		len;

	len = 0;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	neg_to_pos(int *n)
{
	if (*n < 0)
	{
		*n = -(*n);
		ft_putchar('-');
	}
}

void		ft_putnbr(int n)
{
	int		len;
	int		div;

	div = 1;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	neg_to_pos(&n);
	len = intlen(n);
	while (len--)
		div *= 10;
	while (div > 0)
	{
		ft_putchar((n / div) % 10 + 48);
		div /= 10;
	}
}
