/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:49:07 by pkingsbl          #+#    #+#             */
/*   Updated: 2020/07/22 15:00:55 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_type_to_str(va_list ap, t_specif spec)
{
	__int128_t	arg;
	char		*res;

	if (spec.type == 'u' || NONDEC)
	{
		arg = va_arg(ap, unsigned long long);
		if (spec.size[0] != 'l')
			arg = (unsigned)arg;
	}
	else
	{
		arg = va_arg(ap, long long);
		if (spec.size[0] != 'l')
			arg = (int)arg;
	}
	if (spec.type == 'x')
		res = ft_for_haxedecimal(arg, spec);
	else if (spec.type == 'X')
		res = ft_for_haxedecimal_up(arg, spec);
	else if (spec.type == 'i' || spec.type == 'd' || spec.type == 'u')
		res = ft_for_decimal(arg, spec, 10);
	else if (spec.type == 'o')
		res = ft_for_decimal(arg, spec, 8);
	else
		return (NULL);
	return (res);
}

int			ft_solve_type(va_list ap, int fd, t_specif spec)
{
	char	*str;
	int		i;

	str = NULL;
	if (spec.type == 'c')
		return (ft_for_char(ap, &spec));
	else if (spec.type == 's')
		str = ft_for_string(ap, spec);
	else if (spec.type == 'u' || spec.type == 'x' ||
	spec.type == 'X' || spec.type == 'o' || spec.type == 'd' ||
	spec.type == 'i')
		str = ft_type_to_str(ap, spec);
	else if (spec.type == 'p')
		str = ft_for_p(ap, spec);
	else if (spec.type == '%')
		str = ft_for_percent(spec);
	else if (spec.type == 'f')
		str = ft_for_ld(ap, spec);
	ft_putstr_fd(str, fd);
	i = ft_strlen(str);
	ft_strdel(&str);
	return (i);
}

const char	*ft_search_spec(const char *format, t_specif *spec, va_list ap)
{
	ft_spec_new(spec);
	if (*format == '\0')
		return (NULL);
	format = search_flags(format, spec);
	if (spec->plus == 1)
		spec->space = 0;
	if (spec->minus == 1)
		spec->zero = 0;
	format = search_wide(format, spec, ap);
	if (*format == '.')
		format = search_precision(format, spec, ap);
	format = search_size(format, spec);
	format = search_type(format, spec);
	if (spec->type == 'u')
	{
		spec->space = 0;
		spec->plus = 0;
	}
	return (format);
}

void		ft_spec_new(t_specif *spec)
{
	spec->sharp = 0;
	spec->zero = 0;
	spec->minus = 0;
	spec->plus = 0;
	spec->space = 0;
	spec->wide = 0;
	spec->precision = -1;
	spec->size[0] = '\0';
	spec->size[1] = '\0';
	spec->size[2] = '\0';
	spec->type = '\0';
	spec->res = NULL;
}

int			ft_fdprintf(int fd, const char *format, ...)
{
	int			i;
	va_list		ap;
	t_specif	spec;

	i = 0;
	if (!format)
		return (0);
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format != '%')
			format += print_not_percent(format, &i, fd);
		if (*format == '%')
		{
			format++;
			if ((format = ft_search_spec(format, &spec, ap)) == NULL)
				return (0);
			i += ft_solve_type(ap, fd, spec);
		}
	}
	va_end(ap);
	return (i);
}
