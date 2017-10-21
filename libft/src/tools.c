/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 15:44:19 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/15 18:33:05 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fprintf.h"

void	init_struct(t_printf *print)
{
	print->buff = NULL;
	print->buff_size = 0;
	print->ret = 0;
	print->is_percent_c = 0;
	print->is_percent_s = 0;
	print->is_percent_d = 0;
	print->i = 0;
}

void	print_buff(t_printf *print, int *fd)
{
	print->buff[print->i] = '\0';
	ft_putstr_fd(print->buff, *fd);
	free(print->buff);
}
