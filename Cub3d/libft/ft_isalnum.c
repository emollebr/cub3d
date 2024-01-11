/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:04:20 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 11:55:44 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	c = 'A';
	int	b = '!';
	int	x;
	int	y;

	x = ft_isalnum(c);
	y = ft_isalnum(b);
	printf("%d", x);
	printf("%d", y);
}*/
