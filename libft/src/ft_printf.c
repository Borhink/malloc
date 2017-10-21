/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 15:26:32 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 11:50:08 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(const char *format, va_list *args, int ret)
{
	char	*tmp;
	int		i;
	int		len;
	int		j;

	if (!(*format))
		return (ret);
	len = 0;
	if ((tmp = ft_strchr(format, '%')))
	{
		i = tmp - format;
		if ((j = parse_color(format, tmp, &len)))
			return (print_format(format + j, args, ret + len));
		len += put_nstr(format, i);
		len += parse_arg(&tmp, args, ret + len);
		return (print_format(tmp, args, ret + len));
	}
	if ((j = parse_color(format, format + ft_strlen(format), &len)))
		return (print_format(format + j, args, ret + len));
	ft_putstr(format);
	ret += ft_strlen(format);
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	va_list args;
	int		ret;

	va_start(args, format);
	ret = print_format(format, &args, 0);
	va_end(args);
	return (ret);
}
