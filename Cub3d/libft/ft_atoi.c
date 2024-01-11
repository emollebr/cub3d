/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:07:48 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 12:44:29 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static int	ft_isspace(char nptr)
{
	if ((nptr >= 9 && nptr <= 13) || (nptr == 32))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	val;
	int	res;

	i = 0;
	val = 1;
	res = 0;
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
	res = res * val;
	return (res);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*str;

	str = argv[1];
	if (argc == 2)
	{
		printf("%d\n", ft_atoi(str));
		printf("%d", atoi(str));
	}
}*/
