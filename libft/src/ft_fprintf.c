/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 15:44:19 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/15 18:31:41 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fprintf.h"

void	count_buff_size(t_printf *print, const char *format, va_list pa)
{
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			while (*format == ' ')
				++format;
			if (*format == 'c')
				percent_c(print, pa);
			else if (*format == 'd')
				percent_d(print, pa);
			else if (*format == 's')
				percent_s(print, pa);
			else
				++print->buff_size;
		}
		else
			++print->buff_size;
		++format;
	}
}

void	specifier(const char *format, va_list pa, t_printf *print)
{
	if (*format == 'c')
		percent_c(print, pa);
	else if (*format == 'd' || *format == 'i')
		percent_d(print, pa);
	else if (*format == 's')
		percent_s(print, pa);
}

void	write_string(t_printf *print, const char *format, va_list pa, int *fd)
{
	print->buff = ft_memalloc(print->buff_size + 1);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			while (*format == ' ')
				++format;
			if (*format == '%')
			{
				ft_strcat(print->buff, "%");
				print->i++;
			}
			else
				specifier(format, pa, print);
		}
		else
		{
			print->buff[print->i] = *format;
			++print->i;
		}
		++format;
	}
	print_buff(print, fd);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	t_printf	print;
	va_list		pa;

	va_start(pa, format);
	init_struct(&print);
	if (*format == '%' && ft_strlen(format) == 1)
		return (0);
	count_buff_size(&print, format, pa);
	va_end(pa);
	print.is_percent_s = 1;
	print.is_percent_d = 1;
	print.is_percent_c = 1;
	va_start(pa, format);
	write_string(&print, format, pa, &fd);
	va_end(pa);
	return (ft_strlen(print.buff));
}
