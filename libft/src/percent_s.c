/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:06:29 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/15 18:32:56 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fprintf.h"

void	percent_s(t_printf *print, va_list pa)
{
	char	*s;

	s = va_arg(pa, char *);
	if (print->is_percent_s == 1)
	{
		if (s == 0)
		{
			ft_strcat(print->buff, "(null)");
			print->i += 6;
		}
		else
		{
			ft_strcat(print->buff, s);
			print->i += ft_strlen(s);
		}
	}
	if (s == 0)
	{
		print->buff_size += 6;
		return ;
	}
	else
		print->buff_size += ft_strlen(s);
}
