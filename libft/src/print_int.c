/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 02:39:37 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 00:11:41 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_arg(va_list *args, t_param *p)
{
	get_wild_arg(args, p);
	if (p->lgt == 'l')
		return (ft_ltoa(va_arg(*args, long)));
	else if (p->lgt == 'L')
		return (ft_lltoa(va_arg(*args, long long)));
	else if (p->lgt == 'h')
		return (ft_sitoa(va_arg(*args, int)));
	else if (p->lgt == 'H')
		return (ft_sctoa(va_arg(*args, int)));
	else if (p->lgt == 'j')
		return (ft_imtoa(va_arg(*args, intmax_t)));
	else if (p->lgt == 'z')
		return (ft_stoa(va_arg(*args, size_t)));
	else
		return (ft_itoa(va_arg(*args, int)));
}

int			print_int(va_list *args, t_param *p)
{
	char	*str;
	char	ret;

	ret = 0;
	str = get_arg(args, p);
	if (p->flag[PLUS] && *str != '-')
		str = strjoin_n_free("+", str);
	p->neg = (*str == '-' ? 1 : 0);
	str = adjust_prec(str, p);
	if (*str == '0' && (p->flag[MIN] || p->prec >= 0))
		p->flag[ZERO] = 0;
	if ((p->neg || p->flag[PLUS]) && p->flag[ZERO])
		ft_putchar(*str);
	if (!p->flag[MIN])
		ret += put_blank(ft_strlen(str), p) + ft_strlen(str);
	(p->neg || p->flag[PLUS]) && p->flag[ZERO] ?
		ft_putstr(str + 1) : ft_putstr(str);
	if (p->flag[MIN])
		ret += put_blank(ft_strlen(str), p) + ft_strlen(str);
	free(str);
	return (ret);
}
