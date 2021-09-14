/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:27:43 by pkingsbl          #+#    #+#             */
/*   Updated: 2020/02/12 16:47:14 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

const char	*search_flags(const char *str, t_specif *spec)
{
	while (*str == '#' || *str == '0' || *str == '-' || *str == '+' ||
			*str == ' ')
	{
		if (*str == '#')
			spec->sharp = 1;
		else if (*str == '0')
			spec->zero = 1;
		else if (*str == '-')
			spec->minus = 1;
		else if (*str == '+')
			spec->plus = 1;
		else if (*str == ' ')
			spec->space = 1;
		str++;
	}
	return (str);
}

const char	*search_wide(const char *str, t_specif *spec, va_list ap)
{
	if (*str == '*')
	{
		spec->wide = va_arg(ap, int);
		if (spec->wide < 0)
		{
			spec->wide = spec->wide * (-1);
			spec->minus = 1;
			spec->zero = 0;
		}
		str++;
	}
	if ((*str < 48) || (*str > 57))
		return (str);
	else
	{
		spec->wide = ft_atoi(str);
		while ((*str > 47) && (*str < 58))
			str++;
	}
	return (str);
}

const char	*search_precision(const char *str, t_specif *spec, va_list ap)
{
	str++;
	spec->precision = 0;
	if (*str == '*')
	{
		spec->precision = va_arg(ap, int);
		str++;
	}
	if ((*str < 48) || (*str > 57))
		return (str);
	spec->precision = ft_atoi(str);
	if (spec->precision < -1)
		spec->precision = -1;
	while ((*str > 47) && (*str < 58))
		str++;
	return (str);
}

const char	*search_size(const char *str, t_specif *spec)
{
	if (*str != 'l' && *str != 'h' && *str != 'L')
		return (str);
	if (*str == 'L')
	{
		spec->size[0] = 'L';
		str++;
		return (str);
	}
	if (*str == 'l' || *str == 'h')
	{
		spec->size[0] = *str;
		str++;
		if ((*str == 'l' || *str == 'h') && *str == spec->size[0])
		{
			spec->size[1] = *str;
			str++;
		}
	}
	return (str);
}

const char	*search_type(const char *str, t_specif *spec)
{
	if (*str == 'c' || *str == 'd' || *str == 'i' || *str == 'f' ||
	*str == 'o' || *str == 's' || *str == 'u' || *str == 'x' ||
	*str == 'X' || *str == 'p' || *str == '%')
		spec->type = *str;
	else
		return (NULL);
	str++;
	return (str);
}
