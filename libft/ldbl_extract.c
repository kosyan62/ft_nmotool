/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldbl_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:39:06 by mgena             #+#    #+#             */
/*   Updated: 2019/12/22 20:29:30 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ldbl_header.h"

t_specif	ft_spec_when_nan(t_specif spec)
{
	spec.zero = 0;
	spec.sharp = 0;
	spec.precision = 0;
	return (spec);
}

char		*ft_get_ldbl(t_specif *spec, long double x)
{
	char *str;

	if (spec->precision == -1)
		str = (print_float(x, 6));
	else
		str = (print_float(x, spec->precision));
	if (x != x || x == 1. / 0 || x == -1. / 0)
		*spec = ft_spec_when_nan(*spec);
	if (spec->precision == 0 && spec->sharp == 1 && x == x)
		str = ft_strjoin(str, ".");
	if (spec->plus == 1)
	{
		if (x >= 0 && str[0] != '-')
			str = ft_strjoin("+", str);
		spec->space = 0;
	}
	if (spec->space == 1 && x >= 0 && str[0] != '-')
		str = ft_strjoin(" ", str);
	if (spec->minus == 1)
		spec->zero = 0;
	return (str);
}

char		*ft_ldbl_shift(char *str, t_specif spec)
{
	char *tmp;

	tmp = ft_strright(&str, spec.precision, '0');
	if (spec.wide != 0)
	{
		if (spec.minus == 1)
		{
			if (spec.zero == 1)
				tmp = ft_strleft(&tmp, spec.wide, '0');
			else
				tmp = ft_strleft(&tmp, spec.wide, ' ');
		}
		else if (spec.minus == 0)
		{
			if (spec.zero == 1)
				tmp = ft_strright(&tmp, spec.wide, '0');
			else
				tmp = ft_strright(&tmp, spec.wide, ' ');
		}
	}
	return (tmp);
}

char		*ft_for_ld(va_list ap, t_specif spec)
{
	long double	x;
	char		*tmp;
	char		*str;

	if (ft_strcmp(spec.size, "L") == 0)
		x = va_arg(ap, long double);
	else
		x = va_arg(ap, double);
	str = ft_get_ldbl(&spec, x);
	tmp = ft_ldbl_shift(str, spec);
	return (tmp);
}

char		*reverse_str(char *str)
{
	char	res[BUFSIZE];
	int		i;
	int		k;

	i = 0;
	ft_bzero(res, BUFSIZE);
	k = ft_strlen(str) - 1;
	ft_strcpy(res, str);
	while (k >= 0)
		res[i++] = str[k--];
	res[i] = 0;
	ft_strcpy(str, res);
	return (str);
}
