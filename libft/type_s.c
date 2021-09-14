/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:19:26 by pkingsbl          #+#    #+#             */
/*   Updated: 2020/07/22 15:46:22 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_for_string(va_list ap, t_specif spec)
{
	char	*tmp;

	tmp = va_arg(ap, char*);
	if (tmp == NULL)
	{
		free(tmp);
		tmp = ft_strdup("(null)");
		spec.len = 6;
	}
	else
		tmp = ft_strdup(tmp);
	if (spec.precision > -1 && spec.precision < (int)ft_strlen(tmp))
		tmp[spec.precision] = '\0';
	if (spec.wide != 0 && (spec.wide > (int)ft_strlen(tmp)))
	{
		if (spec.minus == 1)
			tmp = ft_strleft(&tmp, spec.wide, ' ');
		else if (spec.minus == 0)
			tmp = ft_strright(&tmp, spec.wide, ' ');
	}
	return (tmp);
}

char	*ft_strleft(char **str, int wide, char s)
{
	int		i;
	char	*res;

	i = 0;
	if (wide < (int)ft_strlen(*str))
		return (*str);
	res = ft_strnew(wide);
	while ((*str)[i])
	{
		res[i] = (*str)[i];
		i++;
	}
	while (i < wide)
	{
		res[i] = s;
		i++;
	}
	res[i] = '\0';
	free(*str);
	return (res);
}

void	stroka_25(char **str, char s, char **res, int zeropoint)
{
	if ((*str)[0] == '-' && s == '0')
	{
		(*res)[zeropoint + 1] = '0';
		(*res)[0] = '-';
	}
	else if ((*str)[0] == '+' && s == '0')
	{
		(*res)[zeropoint + 1] = '0';
		(*res)[0] = '+';
	}
	else if ((*str)[0] == ' ' && s == '0')
	{
		(*res)[zeropoint + 1] = '0';
		(*res)[0] = ' ';
	}
	else if ((*str)[1] == 'x' && s == '0')
	{
		(*res)[zeropoint + 2] = '0';
		(*res)[1] = 'x';
	}
}

char	*ft_strright(char **str, int wide, char s)
{
	char	*res;
	int		zeropoint;
	char	*tmp;

	wide -= ft_strlen(*str) + 1;
	if (wide < 0)
		return (*str);
	res = ft_strnew(wide + ft_strlen(*str));
	zeropoint = wide;
	while (wide >= 0)
		res[wide--] = s;
	tmp = res;
	res = ft_strjoin(tmp, *str);
	free(tmp);
	stroka_25(str, s, &res, zeropoint);
	free(*str);
	return (res);
}

void	str_flags(char **str, char *s1)
{
	char	*help;

	help = (*str);
	(*str) = ft_strjoin(s1, help);
	free(help);
}
