/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:12:12 by mgena             #+#    #+#             */
/*   Updated: 2020/07/22 15:55:49 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	stupid_function_for_25_lines_without_ternary(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	int		d;
	char	*res;

	d = ft_countdigits(n);
	d += stupid_function_for_25_lines_without_ternary(n);
	res = ft_strnew(d);
	if (res == NULL)
		return (NULL);
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strcpy(res, "-2147483648"));
		res[0] = '-';
		n = -n;
	}
	else if (n == 0)
		ft_strcpy(res, "0");
	while (n != 0)
	{
		res[d - 1] = n % 10 + '0';
		d--;
		n /= 10;
	}
	return (res);
}
