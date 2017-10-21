/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:44:40 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/21 16:50:48 by qhonore          ###   ########.fr       */
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

# define ALIGN_4(x) (((((x) - 1 ) >> 2) << 2) + 4)

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
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

int		init_zones(t_env *env);

#endif
