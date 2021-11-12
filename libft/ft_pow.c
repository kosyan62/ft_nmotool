/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:13:26 by mgena             #+#    #+#             */
/*   Updated: 2020/03/05 14:50:04 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_pow(int a, int b)
{
	long	res;

	if (b == 0)
		return (1);
	res = 1;
	while (b != 0)
	{
		res *= a;
		b--;
	}
	return (res);
}
