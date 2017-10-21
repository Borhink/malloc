/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 04:57:37 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 11:51:50 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_precision(char **tmp, t_param *p)
{
	p->prec = -1;
	if (**tmp == '.')
	{
		(*tmp)++;
		p->prec = 0;
		while (ft_isdigit(**tmp) || **tmp == '*')
		{
			if (**tmp == '*')
				p->flag[PWILD] = 1;
			else
				p->prec = p->prec * 10 + (**tmp - '0');
			(*tmp)++;
		}
	}
	return (**tmp ? 1 : 0);
}

static void	parse_width_digits(char **tmp, t_param *p)
{
	while (ft_isdigit(**tmp) || **tmp == '*')
	{
		if (**tmp == '*')
		{
			p->flag[WILD] = 1;
			p->lwth = 0;
		}
		else
		{
			p->lwth = p->lwth * 10 + (**tmp - '0');
			if (p->flag[WILD] == 1)
				p->flag[WILD] = -1;
		}
		(*tmp)++;
	}
}

static int	parse_width_flag(char **tmp, t_param *p)
{
	int		i;

	p->lwth = 0;
	p->neg = 0;
	i = -1;
	while (++i < 7)
		p->flag[i] = 0;
	while (valid_flag(**tmp))
	{
		p->flag[valid_flag(**tmp) - 1] = **tmp;
		(*tmp)++;
	}
	parse_width_digits(tmp, p);
	return (**tmp ? 1 : 0);
}

static int	parse_length(char **tmp, t_param *p)
{
	p->lgt = 0;
	if (valid_length(**tmp))
	{
		p->lgt = **tmp;
		(*tmp)++;
		if (**tmp == p->lgt)
		{
			p->lgt = ft_toupper(p->lgt);
			(*tmp)++;
		}
	}
	return (**tmp ? 1 : 0);
}

int			parse_arg(char **tmp, va_list *args, int g_ret)
{
	int		ret;
	t_param	p;

	ret = 0;
	p.ret = g_ret;
	(*tmp)++;
	if (!parse_width_flag(tmp, &p) || !parse_length(tmp, &p)
	|| !parse_precision(tmp, &p))
		return (ret);
	ret = print_arg(**tmp, args, &p);
	(*tmp)++;
	return (ret);
}
