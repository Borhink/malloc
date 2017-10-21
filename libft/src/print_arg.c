/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 05:00:06 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 13:04:33 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	n_arg(va_list *args, t_param *p)
{
	int		*var;

	var = va_arg(*args, int*);
	*var = p->ret;
	return (0);
}

static int	print_arg2(char type, va_list *args, t_param *p)
{
	if (type == 'x')
		return (print_hexa_uint(args, 0, p));
	if (type == 'X')
		return (print_hexa_uint(args, 1, p));
	if (type == 'u')
		return (print_uint(args, p));
	if (type == 'U')
	{
		p->lgt = 'l';
		return (print_uint(args, p));
	}
	if (type == 'c')
		return (print_char(args, p));
	if (type == 'C')
		return (print_utfchar(args, p));
	if (type == 'n')
		return (n_arg(args, p));
	if (type == 'b')
		return (print_base_uint(args, p));
	if (type == 'r')
		return (print_file(args));
	return (print_blankchar(type, p));
}

int			print_arg(char type, va_list *args, t_param *p)
{
	p->type = type;
	if (type == 'd' || type == 'i')
		return (print_int(args, p));
	if (type == 'D')
	{
		p->lgt = 'l';
		return (print_int(args, p));
	}
	if (type == 's')
		return (print_str(args, p));
	if (type == 'S')
		return (print_utfstr(args, p));
	if (type == 'p')
		return (print_ptr(args, p));
	if (type == 'o')
		return (print_octal_uint(args, p));
	if (type == 'O')
	{
		p->lgt = 'l';
		return (print_octal_uint(args, p));
	}
	return (print_arg2(type, args, p));
}
