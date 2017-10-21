/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 03:01:06 by qhonore           #+#    #+#             */
/*   Updated: 2016/09/27 03:19:15 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_wild_arg(va_list *args, t_param *p)
{
	int		tmp;

	if (p->flag[WILD])
	{
		tmp = va_arg(*args, int);
		if (p->flag[WILD] != -1)
		{
			if (tmp < 0)
			{
				tmp = -tmp;
				p->flag[MIN] = 1;
			}
			if (tmp > p->lwth)
				p->lwth = tmp;
		}
	}
	if (p->flag[PWILD])
		p->prec = va_arg(*args, int);
}

char	*adjust_prec(char *str, t_param *p)
{
	int		len;
	int		sign;
	char	*ret;
	int		i;

	sign = (*str == '+' || *str == '-' ? 1 : 0);
	len = ft_strlen(str + sign);
	if (p->prec > len)
	{
		ret = (char*)malloc(sizeof(char) * (p->prec + sign + 1));
		if (sign)
			*ret = *str;
		p->prec -= len;
		i = sign ? 0 : -1;
		while (++i < p->prec + sign)
			ret[i] = '0';
		ret[p->prec + len + sign] = '\0';
		while (--len >= 0)
			ret[i + len] = str[len + sign];
		free(str);
		return (ret);
	}
	else if (p->prec == 0 && *(str + sign) == '0')
		*(str + sign) = '\0';
	return (str);
}

int		put_nstr(const char *str, int n)
{
	if (str && (int)(ft_strlen(str)) >= n)
	{
		write(1, str, n);
		return (n);
	}
	else
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
}

int		put_blank(int len, t_param *p)
{
	int		ret;

	if (p->lwth < 1 && p->flag[BLANK] && !p->neg
		&& valid_int(p->type) && !p->flag[PLUS])
	{
		ft_putchar(' ');
		return (1);
	}
	if (p->flag[MIN])
		p->flag[ZERO] = 0;
	p->lwth -= len;
	ret = p->lwth > 0 ? p->lwth : 0;
	while (p->lwth-- > 0)
	{
		if (p->flag[BLANK] && !p->flag[PLUS]
			&& !p->neg && p->type != 'p')
		{
			p->flag[BLANK] = 0;
			ft_putchar(' ');
		}
		else
			ft_putchar(p->flag[ZERO] ? '0' : ' ');
	}
	return (ret);
}

char	*strjoin_n_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s2);
	return (str);
}
