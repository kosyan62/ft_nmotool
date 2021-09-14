/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:41:03 by mgena             #+#    #+#             */
/*   Updated: 2019/12/22 20:30:05 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ldbl_header.h"

void		long_add_extrapart(char *num, char *res, int flag, int tmp)
{
	int	i;

	i = 0;
	while (num[i] != 0)
	{
		tmp = num[i] - '0' + flag;
		res[i++] = tmp % 10 + '0';
		if (tmp > 9)
			flag = 1;
		else
			flag = 0;
	}
	if (flag == 1)
		res[i++] = '1';
	res[i] = 0;
}

void		long_add(char *num1, char *num2)
{
	int		i;
	char	res[BUFSIZE];
	int		tmp;
	_Bool	flag;

	i = 0;
	flag = 0;
	ft_bzero(res, BUFSIZE);
	while (num1[i] != 0 && num2[i] != 0)
	{
		tmp = (num1[i] - '0') + (num2[i] - '0') + flag;
		res[i++] = tmp % 10 + '0';
		if (tmp > 9)
			flag = 1;
		else
			flag = 0;
	}
	if (num1[i] == 0 && num2[i] == 0 && flag == 1)
		res[i++] = '1';
	else if (num1[i] == 0)
		long_add_extrapart(&num2[i], &res[i], flag, tmp);
	else if (num2[i] == 0)
		long_add_extrapart(&num1[i], &res[i], flag, tmp);
	ft_strcpy(num1, res);
}

void		long_math_multiply(char *p, int pow)
{
	int		i;
	int		flag;
	int		numint;

	i = 0;
	flag = 0;
	while (p[i] != 0)
	{
		numint = (p[i] - '0') * pow;
		p[i++] = numint % 10 + flag + '0';
		if (numint > 9)
			flag = numint / 10;
		else
			flag = 0;
	}
	if (flag != 0)
		p[i++] = flag + '0';
}

void		long_math_power(int n, char *end, int pow, int i)
{
	char res[BUFSIZE];

	ft_bzero(res, BUFSIZE);
	if (i != 0)
		ft_memset(res, '0', n);
	if (n == 0)
	{
		end[0] = '1';
		end[1] = 0;
		return ;
	}
	*res = pow + '0';
	res[1] = 0;
	while (n-- != 1)
		long_math_multiply(res, pow);
	ft_strcpy(end, res);
}

long double	power_two(int ei)
{
	if (ei == 0)
		return (1);
	else if (ei == 1)
		return (2);
	else
		return (2 * power_two(ei - 1));
}
