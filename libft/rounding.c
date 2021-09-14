/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:44:32 by mgena             #+#    #+#             */
/*   Updated: 2019/12/22 18:44:32 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ldbl_header.h"

void	long_add_div(char xm[BUFSIZE], char ym[BUFSIZE])
{
	char	x[BUFSIZE];
	char	y[BUFSIZE];
	int		lenx;
	int		leny;

	lenx = ft_strlen(xm);
	leny = ft_strlen(ym);
	ft_strcpy(x, reverse_str(xm));
	ft_strcpy(y, reverse_str(ym));
	ft_memset(&x[lenx], '0', leny - lenx);
	ft_strcpy(xm, reverse_str(x));
	ft_strcpy(ym, reverse_str(y));
	long_add(xm, ym);
}

int		round_bedot(int ad, char *x, char *xm)
{
	int i;

	i = 0;
	reverse_str(xm);
	while (i != ad && xm[i] == '9')
		i++;
	if (ad == 0 && xm[0] >= '5' && xm[0] <= '9' && xm[1] != '\0')
		long_add(x, "1");
	else if (xm[ad - 1] == '9' && xm[ad] > '5' && i == ad && ad != 0)
	{
		long_add(x, "1");
		ft_memset(xm, '0', ad);
		xm[ad] = 0;
	}
	else
	{
		i = 0;
	}
	return (i);
}

void	rounding(char x[BUFSIZE], char xm[BUFSIZE], int afterdot)
{
	int		i;
	char	array[BUFSIZE];
	char	plus[BUFSIZE];

	i = round_bedot(afterdot, x, xm);
	ft_bzero(array, BUFSIZE);
	ft_bzero(plus, BUFSIZE);
	while (i != afterdot && xm[i] != 0)
	{
		array[i] = xm[i];
		plus[i++] = '0';
	}
	if (xm[i] < '5' && xm[i] > '0')
		plus[i - 1] = '0';
	else if ((xm[i] >= '5' && xm[i] <= '9'))
		plus[i - 1] = '1';
	long_add(reverse_str(array), reverse_str(plus));
	reverse_str(array);
	ft_bzero(xm, BUFSIZE);
	ft_strncpy(xm, array, afterdot);
	i = 0;
	while (xm[i] != 0)
		i++;
	while (i != afterdot)
		xm[i++] = '0';
}
