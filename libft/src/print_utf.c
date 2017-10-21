/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 02:16:30 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 03:25:26 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_nullwstr(t_param *p)
{
	int		ret;

	if (p->lwth < 1)
		return (ft_putstr("(null)"));
	ret = p->lwth;
	while (--p->lwth >= 0)
		ft_putchar('0');
	return (ret);
}

static int	put_utfstr(t_param *p, wchar_t *wstr)
{
	int		i;
	int		cut;
	int		ret;

	cut = 0;
	i = 0;
	ret = 0;
	if (p->prec >= 0 && p->prec < utf_strlen(wstr))
	{
		wstr = utf_strsub(wstr, 0, p->prec);
		cut = 1;
	}
	if (!p->flag[MIN])
		ret += put_blank(utf_strlen(wstr), p);
	while (wstr[i])
		ret += put_utfchar(wstr[i++]);
	if (p->flag[MIN])
		ret += put_blank(utf_strlen(wstr), p);
	if (cut && wstr)
		free(wstr);
	return (ret);
}

int			print_utfstr(va_list *args, t_param *p)
{
	wchar_t	*wstr;
	int		ret;

	get_wild_arg(args, p);
	wstr = va_arg(*args, wchar_t *);
	if (!wstr)
		return (print_nullwstr(p));
	ret = put_utfstr(p, wstr);
	return (ret);
}

int			print_utfchar(va_list *args, t_param *p)
{
	int		ret;
	wint_t	wc;

	get_wild_arg(args, p);
	wc = va_arg(*args, wint_t);
	ret = 0;
	if (!p->flag[MIN])
		ret += put_blank(utfchar_len(wc), p);
	ret += put_utfchar(wc);
	if (p->flag[MIN])
		ret += put_blank(utfchar_len(wc), p);
	return (ret);
}
