/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:25:05 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 13:11:00 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_blankchar(char c, t_param *p)
{
	int		ret;

	if (!p->flag[MIN])
		ret = put_blank(1, p) + 1;
	ft_putchar(c);
	if (p->flag[MIN])
		ret = put_blank(1, p) + 1;
	return (ret);
}

static int	print_nullstr(t_param *p)
{
	int		ret;

	if (p->lwth < 1 || p->flag[WILD])
		return (ft_putstr("(null)"));
	ret = p->lwth;
	while (--p->lwth >= 0)
		ft_putchar('0');
	return (ret);
}

int			print_str(va_list *args, t_param *p)
{
	char	*str;
	int		ret;
	int		cut;

	cut = 0;
	if (p->lgt == 'l')
		return (print_utfstr(args, p));
	get_wild_arg(args, p);
	str = va_arg(*args, char *);
	if (!str)
		return (print_nullstr(p));
	if (p->prec >= 0 && (size_t)p->prec < ft_strlen(str))
	{
		str = ft_strsub(str, 0, p->prec);
		cut = 1;
	}
	if (!p->flag[MIN])
		ret = put_blank(ft_strlen(str), p) + ft_strlen(str);
	ft_putstr(str);
	if (p->flag[MIN])
		ret = put_blank(ft_strlen(str), p) + ft_strlen(str);
	if (cut && str)
		free(str);
	return (ret);
}

int			print_char(va_list *args, t_param *p)
{
	int		ret;

	if (p->lgt == 'l')
		return (print_utfchar(args, p));
	if (!p->flag[MIN])
		ret = put_blank(1, p) + 1;
	get_wild_arg(args, p);
	ft_putchar(va_arg(*args, int));
	if (p->flag[MIN])
		ret = put_blank(1, p) + 1;
	return (ret);
}

int			print_file(va_list *args)
{
	char	*line;
	int		ret;
	int		fd;

	ret = 0;
	if ((fd = open(va_arg(*args, char*), O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			ret += ft_putstr(line);
			ret += ft_putchar('\n');
			if (line)
				free(line);
		}
		close(fd);
	}
	return (ret);
}
