/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:41:29 by mgena             #+#    #+#             */
/*   Updated: 2019/12/22 20:28:08 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ldbl_header.h"

char	*nan_str(long double n)
{
	char *res;

	res = ft_strnew(5);
	if (n != n)
		return (ft_strcpy(res, "nan"));
	else if (n == 1. / 0)
		return (ft_strcpy(res, "inf"));
	else if (n == -1. / 0)
		return (ft_strcpy(res, "-inf"));
	else
		return (NULL);
}

char	*get_ldbl_str_final(t_lng_dbl ld, char *x, char *xm, long long ad)
{
	char *res;
	char *tmp;

	if (ld.t_bit_long_double.sign == 1)
		tmp = ft_strjoin("-", reverse_str(x));
	else
		tmp = ft_strdup(reverse_str(x));
	if (ad != 0)
	{
		res = ft_strjoin(tmp, ".");
		free(tmp);
		tmp = res;
	}
	res = ft_strjoin(tmp, xm);
	free(tmp);
	return (res);
}

void	ldbl_work(int i[2], int shift, char x[3][BUFSIZE], t_lng_dbl ld)
{
	while (i[1] >= 0 && i[0] < 64)
	{
		if (((ld.t_bit_long_double.mantissa >> shift) & 1) == 1)
		{
			long_math_power(i[1], x[1], 2, 0);
			long_add(x[0], x[1]);
		}
		i[1]--;
		shift--;
		i[0]++;
	}
	ft_bzero(x[1], BUFSIZE);
	i[1] = -i[1];
	while (i[0] < 64)
	{
		if (((ld.t_bit_long_double.mantissa >> shift) & 1) == 1)
		{
			long_math_power(i[1], x[1], 5, i[1]);
			long_add_div(x[2], x[1]);
		}
		i[1]++;
		shift--;
		i[0]++;
	}
}

char	*print_float(long double n, long long afterdot)
{
	t_lng_dbl		ld;
	int				bit_shift;
	char			x[3][BUFSIZE];
	int				i[2];

	i[0] = 0;
	ld.ldbl = n;
	bit_shift = 63;
	if (n != n || n == 1. / 0 || n == -1. / 0)
		return (nan_str(n));
	ft_bzero(x[0], BUFSIZE);
	ft_bzero(x[1], BUFSIZE);
	ft_bzero(x[2], BUFSIZE);
	i[1] = ld.t_bit_long_double.exponent - 16383;
	x[0][0] = '0';
	x[2][0] = '0';
	ldbl_work(i, bit_shift, x, ld);
	rounding(x[0], x[2], afterdot);
	return (get_ldbl_str_final(ld, x[0], x[2], afterdot));
}
