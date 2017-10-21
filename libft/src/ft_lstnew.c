/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:29:26 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/17 13:23:37 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlist;

	if (!(newlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
	}
	else
	{
		if (!(newlist->content = malloc(content_size)))
		{
			free(newlist);
			return (NULL);
		}
		ft_memcpy(newlist->content, content, content_size);
		newlist->content_size = content_size;
	}
	newlist->next = NULL;
	return (newlist);
}

t_list	*ft_lstnew_n(void *content, size_t content_size)
{
	t_list *newlist;

	if (!(newlist = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
	}
	else
	{
		newlist->content = content;
		newlist->content_size = content_size;
	}
	newlist->next = NULL;
	return (newlist);
}
