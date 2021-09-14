/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:19:23 by pkingsbl          #+#    #+#             */
/*   Updated: 2019/12/22 20:41:12 by pkingsbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_for_percent(t_specif spec)
{
	char	*str;
	char	*res;

	res = NULL;
	str = ft_strnew(2);
	str[0] = '%';
	if (spec.wide != 0)
	{
		if (spec.minus == 1)
			str = ft_strleft(&str, spec.wide, ' ');
		else if (spec.minus == 0)
		{
			if (spec.zero == 1)
				str = ft_strright(&str, spec.wide, '0');
			else
				str = ft_strright(&str, spec.wide, ' ');
		}
	}
	return (str);
}
