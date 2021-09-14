/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:45:57 by mgena             #+#    #+#             */
/*   Updated: 2020/07/22 15:00:13 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_printf(const char *format, ...)
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
			format += print_not_percent(format, &i, STDOUT_FILENO);
		if (*format == '%')
		{
			format++;
			if ((format = ft_search_spec(format, &spec, ap)) == NULL)
				return (0);
			i += ft_solve_type(ap, STDOUT_FILENO, spec);
		}
	}
	va_end(ap);
	return (i);
}
