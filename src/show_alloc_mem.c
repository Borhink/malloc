/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:09:39 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/25 18:54:49 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	ft_len(size_t nb, int base)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= base;
		len++;
	}
	return (len);
}

static void	print_unsigned(unsigned long nb, int base, int x)
{
	const char	num[] = "0123456789ABCDEF\0";
	char		str[64];
	int			len;

	len = ft_len(nb, base);
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = num[nb % base];
		nb /= base;
	}
	if (x)
		ft_putstr("0x");
	ft_putstr(str);
}

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
			print_unsigned((unsigned long)ptr, 16, 1);
			ft_putstr(" - ");
			print_unsigned((unsigned long)ptr + block->size, 16, 1);
			ft_putstr(" : ");
			print_unsigned(block->size, 10, 0);
			block->size > 1 ? ft_putstr(" octets\n") : ft_putstr(" octet\n");
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

	ft_putstr("TINY : ");
	print_unsigned((unsigned long)e->tiny, 16, 1);
	ft_putstr("\n");
	size = show_zone(e->tiny);
	ft_putstr("SMALL : ");
	print_unsigned((unsigned long)e->small, 16, 1);
	ft_putstr("\n");
	size += show_zone(e->small);
	ft_putstr("LARGE : ");
	print_unsigned((unsigned long)e->large, 16, 1);
	ft_putstr("\n");
	size += show_zone(e->large);
	ft_putstr("Total : ");
	print_unsigned(size, 10, 0);
	size > 1 ? ft_putstr(" octets\n") : ft_putstr(" octet\n");
}
