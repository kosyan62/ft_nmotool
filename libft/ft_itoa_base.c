/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:54:46 by mgena             #+#    #+#             */
/*   Updated: 2019/12/22 20:39:18 by pkingsbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdint.h>

int		ft_countdigits_base(__int128_t n, int base)
{
	int		res;

	if (n == 0)
		return (1);
	res = 0;
	while (n != 0)
	{
		res++;
		n /= base;
	}
	return (res);
}

char	*ft_itoa_base(__int128_t n, int base)
{
	int		d;
	char	*res;
	char	*array;

	array = "0123456789abcdef";
	d = ft_countdigits_base(n, base);
	d = (n < 0) ? ++d : d;
	res = ft_strnew(d);
	if (res == NULL)
		return (NULL);
	if (n < 0)
	{
		if (n == INT64_MIN)
			return (ft_strcpy(res, "-9223372036854775808"));
		res[0] = '-';
		n = -n;
	}
	res = (n == 0) ? ft_strcpy(res, "0") : res;
	while (n != 0)
	{
		res[d - 1] = array[n % base];
		d--;
		n /= base;
	}
	return (res);
}
