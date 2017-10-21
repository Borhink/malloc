/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:43:33 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/21 16:54:26 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*tiny_malloc(t_env *env)
{
	(void)env;
	printf("env->tiny : %p\n", env->tiny);
	printf("env->small : %p\n", env->small);
	printf("env->tiny->size : %zu\n", env->tiny->size);
	printf("env->tiny->next : %p\n", env->tiny->next);
	printf("env->tiny->free : %d\n", env->tiny->free);
	printf("env->small->size : %zu\n", env->small->size);
	printf("env->small->next : %p\n", env->small->next);
	printf("env->small->free : %d\n", env->small->free);
	return (NULL);
}

void	*malloc(size_t size)
{
	static t_env	env = {NULL, 0, NULL, 0, NULL};

	if (env.tiny == NULL && !init_zones(&env))
		return (NULL);
	if (size > SMALL)
		return (NULL);//LARGE
	else if (size > TINY)
		return (NULL);//SMALL
	else
		return (tiny_malloc(&env));
}
