/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:01:45 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 08:05:06 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_color(char *start, int i)
{
	if (!ft_strncmp(start, "black", i))
		return (ft_putstr(BLACK));
	else if (!ft_strncmp(start, "red", i))
		return (ft_putstr(RED));
	else if (!ft_strncmp(start, "green", i))
		return (ft_putstr(GREEN));
	else if (!ft_strncmp(start, "yellow", i))
		return (ft_putstr(YELLOW));
	else if (!ft_strncmp(start, "blue", i))
		return (ft_putstr(BLUE));
	else if (!ft_strncmp(start, "purple", i))
		return (ft_putstr(PURPLE));
	else if (!ft_strncmp(start, "cyan", i))
		return (ft_putstr(CYAN));
	else if (!ft_strncmp(start, "grey", i))
		return (ft_putstr(GREY));
	else if (!ft_strncmp(start, "pink", i))
		return (ft_putstr(PINK));
	else if (!ft_strncmp(start, "eoc", i))
		return (ft_putstr(EOC));
	return (0);
}

int			parse_color(const char *str, const char *max, int *len)
{
	char	*start;
	char	*end;
	int		i;

	if ((start = ft_strchr(str, '{')) && start < max
	&& *(start + 1) == ':' && (end = ft_strchr(str, '}')))
	{
		i = start - str;
		*len += put_nstr(str, i);
		start += 2;
		i = end - start;
		if (put_color(start, i))
			return (end - str + 1);
	}
	return (0);
}
