/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:44:40 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/26 16:43:19 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include "libft.h"
# include "ft_printf.h"

# define TYPE_TINY 0
# define TYPE_SMALL 1
# define TYPE_LARGE 2

# define TINY 256
# define SMALL 1024

# define ALIGN_24(x) ((x - 1) / 24 * 24 + 24)
# define ALIGN_PAGE(x) ((x - 1) / getpagesize() * getpagesize() + getpagesize())

typedef struct s_block	t_block;
typedef struct s_env	t_env;

struct	s_block
{
	size_t	size;
	t_block	*next;
	int		free;
};

struct	s_env
{
	t_block	*tiny;
	size_t	tiny_size;
	t_block	*small;
	size_t	small_size;
	t_block	*large;
};

void	free(void *ptr);
void	*malloc(size_t size);
void	*calloc(size_t nitems, size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

t_env	*get_env(void);
int		init_zone(t_env *e, int type);
int		create_zone(t_block **block, size_t size);
void	create_block(t_block *block, size_t size);

size_t	ft_strlen(const char *s);
int		ft_putstr(char const *s);
void	ft_bzero(void *s, size_t n);

#endif
