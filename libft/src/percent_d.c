/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 15:05:17 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/15 18:32:48 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fprintf.h"

void	percent_d(t_printf *print, va_list pa)
{
	char	*string;

	string = ft_ltoa(va_arg(pa, long));
	if (print->is_percent_d == 1)
	{
		ft_strcat(print->buff, string);
		print->i += ft_strlen(string);
	}
	else
		print->buff_size += ft_strlen(string);
	free(string);
}
