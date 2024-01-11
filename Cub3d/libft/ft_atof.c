/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:25:29 by emollebr          #+#    #+#             */
/*   Updated: 2023/05/16 13:25:31 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static int	ft_isspace(char nptr)
{
	if ((nptr >= 9 && nptr <= 13) || (nptr == 32))
		return (1);
	return (0);
}

float	ft_atof(const char *nptr)
{
	int	i;
	float	val;
	float	res;
	float	dec;

	i = 0;
	val = 1;
	res = 0;
	dec = 10;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			val = (-1 * val);
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
		while (nptr[i] <= '9' && nptr[i] >= '0')
		{
			res = res + (nptr[i] - '0') / dec;
			dec = dec * 10;
			i++;
		}
	res = res * val;
	return (res);
}
