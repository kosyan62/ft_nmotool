/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldbl_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:52:10 by mgena             #+#    #+#             */
/*   Updated: 2020/02/04 17:59:14 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LDBL_HEADER_H
# define LDBL_HEADER_H
# include "libftprintf.h"
# define BUFSIZE 16384

typedef union	u_long_double
{
	long double	ldbl;
	struct		s_bit_long_double
	{
		unsigned long long	mantissa : 64;
		unsigned			exponent : 15;
		unsigned			sign : 1;
	}			t_bit_long_double;
}				t_lng_dbl;

char			*reverse_str(char *str);
void			long_add_extrapart(char *num, char *res, int flag, int tmp);
void			long_add(char *num1, char *num2);
void			long_math_multiply(char *p, int pow);
void			long_math_power(int n, char *end, int pow, int i);
void			rounding(char x[BUFSIZE], char xm[BUFSIZE], int afterdot);
void			long_add_div(char xm[BUFSIZE], char ym[BUFSIZE]);
#endif
