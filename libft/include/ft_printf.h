/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:40:42 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/27 13:27:22 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

# define MIN 0
# define PLUS 1
# define BLANK 2
# define SHARP 3
# define ZERO 4
# define WILD 5
# define PWILD 6

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define GREY "\033[1;30m"
# define PINK "\033[1;35m"
# define EOC "\033[0m"

typedef struct	s_param
{
	int		type;
	char	lgt;
	char	flag[7];
	int		lwth;
	int		neg;
	int		prec;
	int		ret;
}				t_param;

int				parse_arg(char **tmp, va_list *args, int g_ret);
int				parse_color(const char *str, const char *max, int *len);
int				print_arg(char type, va_list *args, t_param *p);

int				print_int(va_list *args, t_param *p);
int				print_uint(va_list *args, t_param *p);
int				print_char(va_list *args, t_param *p);
int				print_str(va_list *args, t_param *p);
int				print_file(va_list *args);

int				print_ptr(va_list *args, t_param *p);
int				print_hexa_uint(va_list *args, int upper, t_param *p);
int				print_octal_uint(va_list *args, t_param *p);
int				print_base_uint(va_list *args, t_param *p);

void			get_wild_arg(va_list *args, t_param *p);
char			*adjust_prec(char *str, t_param *p);
int				put_nstr(const char *str, int n);
int				print_blankchar(char c, t_param *p);
int				put_blank(int len, t_param *p);
char			*strjoin_n_free(char *s1, char *s2);

int				utf_strlen(wchar_t *wstr);
int				put_utfchar(wint_t c);
int				utfchar_len(wint_t c);
wchar_t			*utf_strsub(wchar_t *wstr, unsigned int start, size_t len);
int				print_utfstr(va_list *args, t_param *p);
int				print_utfchar(va_list *args, t_param *p);

int				valid_int(char c);
int				valid_arg(char c);
int				valid_length(char c);
int				valid_flag(char c);

#endif
