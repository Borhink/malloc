/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:03:21 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/26 18:34:14 by qhonore          ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_putstr(char const *s)
{
	int		len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char*)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
