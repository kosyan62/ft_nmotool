/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_i_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:07:11 by pkingsbl          #+#    #+#             */
/*   Updated: 2019/12/22 20:41:38 by pkingsbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_for_unsigned(long long arg, t_specif spec)
{
	unsigned long long	uarg;
	char				*res;

	uarg = arg;
	res = ft_for_decimal(uarg, spec, 10);
	return (res);
}

char	*ft_for_decimal(__int128_t dec, t_specif spec, int base)
{
	char	*str;

	if (spec.precision > 0 && (spec.space == 1 || spec.plus == 1 || dec < 0))
		spec.precision++;
	if (ft_strcmp("h", spec.size) == 0)
		dec = (spec.type == 'u' || (NONDEC)) ? (unsigned short)dec : (short)dec;
	else if (ft_strcmp("hh", spec.size) == 0)
		dec = (spec.type == 'u' || NONDEC) ? (unsigned char)dec : (char)dec;
	str = (spec.precision == 0 && dec == 0) ? ft_strnew(1) :
			ft_itoa_base(dec, base);
	spec.plus == 1 && dec >= 0 ? str_flags(&str, "+") : NULL;
	spec.space == 1 && dec >= 0 ? str_flags(&str, " ") : NULL;
	if (spec.sharp == 1 && base == 8)
		str = ft_strright(&str, spec.precision - 1, '0');
	else
		str = ft_strright(&str, spec.precision, '0');
	if (spec.sharp == 1 && dec != 0 && base == 16)
		str_flags(&str, "0x");
	else if (spec.sharp == 1 && dec != 0 && base == 8)
		str_flags(&str, "0");
	else if (spec.sharp == 1 && base == 8 && spec.precision != -1)
		str_flags(&str, "0");
	if (spec.wide != 0)
		str_wide(&str, spec);
	return (str);
}

void	str_wide(char **str, t_specif spec)
{
	if (spec.minus == 1)
	{
		if (spec.zero == 1 && spec.precision == -1)
			(*str) = ft_strleft(&(*str), spec.wide, '0');
		else
			(*str) = ft_strleft(&(*str), spec.wide, ' ');
	}
	else if (spec.minus == 0)
	{
		if (spec.zero == 1 && spec.precision == -1)
			(*str) = ft_strright(&(*str), spec.wide, '0');
		else
			(*str) = ft_strright(&(*str), spec.wide, ' ');
	}
}

char	*ft_for_haxedecimal(__int128_t llhex, t_specif spec)
{
	char	*str;

	if (spec.minus == 1)
		spec.zero = 0;
	str = ft_for_decimal(llhex, spec, 16);
	return (str);
}

char	*ft_for_haxedecimal_up(__int128_t arg, t_specif spec)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_for_haxedecimal(arg, spec);
	while (str[i] != 0)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}
