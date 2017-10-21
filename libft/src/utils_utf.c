/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 03:04:27 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/26 03:44:51 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_utfchar(wint_t c)
{
	if (c >= 1114112)
		return (0);
	if (c < 128)
	{
		ft_putchar(c);
		return (1);
	}
	else if (c < 2048)
	{
		ft_putchar(192 | (c >> 6));
		ft_putchar(128 | (c & 63));
		return (2);
	}
	else if (c < 65536)
	{
		ft_putchar(224 | (c >> 12));
		ft_putchar(128 | ((c >> 6) & 63));
		ft_putchar(128 | (c & 63));
		return (3);
	}
	ft_putchar(240 | (c >> 18));
	ft_putchar(128 | ((c >> 12) & 63));
	ft_putchar(128 | ((c >> 6) & 63));
	ft_putchar(128 | (c & 63));
	return (4);
}

int		utf_strlen(wchar_t *wstr)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (wstr[i])
	{
		if (wstr[i] < 128)
			len++;
		else if (wstr[i] < 2048)
			len += 2;
		else if (wstr[i] < 65536)
			len += 3;
		else if (wstr[i] < 1114112)
			len += 4;
		i++;
	}
	return (len);
}

int		utfchar_len(wint_t c)
{
	if (c >= 1114112)
		return (0);
	if (c < 128)
		return (1);
	else if (c < 2048)
		return (2);
	else if (c < 65536)
		return (3);
	return (4);
}

wchar_t	*utf_strsub(wchar_t *wstr, unsigned int start, size_t len)
{
	size_t	i;
	wchar_t	*str;
	size_t	j;

	i = 0;
	j = 0;
	if (!wstr)
		return (NULL);
	str = (wchar_t*)malloc(sizeof(wint_t) * (len + 1));
	if (!str)
		return (NULL);
	while (j + utfchar_len(wstr[start + i]) <= len)
	{
		str[i] = wstr[start + i];
		i++;
		j += utfchar_len(wstr[start + i]);
	}
	str[i] = '\0';
	return (str);
}
