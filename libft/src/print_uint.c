/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 02:57:31 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 03:28:49 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_arg(va_list *args, t_param *p)
{
	get_wild_arg(args, p);
	if (p->lgt == 'l')
		return (ft_ultoa(va_arg(*args, unsigned long)));
	else if (p->lgt == 'L')
		return (ft_ulltoa(va_arg(*args, unsigned long long)));
	else if (p->lgt == 'h')
		return (ft_usitoa(va_arg(*args, unsigned int)));
	else if (p->lgt == 'H')
		return (ft_uctoa(va_arg(*args, unsigned int)));
	else if (p->lgt == 'j')
		return (ft_uimtoa(va_arg(*args, uintmax_t)));
	else if (p->lgt == 'z')
		return (ft_stoa(va_arg(*args, size_t)));
	else
		return (ft_uitoa(va_arg(*args, unsigned int)));
}

int			print_uint(va_list *args, t_param *p)
{
	char	*str;
	char	ret;

	str = get_arg(args, p);
	str = adjust_prec(str, p);
	if (!p->flag[MIN])
		ret = put_blank(ft_strlen(str), p) + ft_strlen(str);
	ft_putstr(str);
	if (p->flag[MIN])
		ret = put_blank(ft_strlen(str), p) + ft_strlen(str);
	free(str);
	return (ret);
}
