/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:25:59 by mgena             #+#    #+#             */
/*   Updated: 2019/12/22 20:39:06 by pkingsbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*pointer(void *ptr)
{
	char			*res;
	char			*addr;
	t_memory_ptr	x;

	res = ft_strnew(11);
	if (res == NULL)
		return (NULL);
	x.ptr = ptr;
	addr = ft_itoa_base(x.mem, 16);
	ft_strcpy(res, "0x");
	ft_strcpy(&res[2], addr);
	ft_strdel(&addr);
	return (res);
}

char	*ft_for_p(va_list ap, t_specif spec)
{
	char *res;
	void *ptr;

	ptr = va_arg(ap, void*);
	res = pointer(ptr);
	if (spec.precision == 0)
		res[2] = 0;
	else if (spec.precision > 0)
		res = ft_strright(&res, spec.precision + 2, '0');
	if (spec.wide != 0)
	{
		if (spec.minus == 1)
			res = ft_strleft(&res, spec.wide, ' ');
		else if (spec.minus == 0)
			res = ft_strright(&res, spec.wide, ' ');
	}
	return (res);
}
