/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:05:47 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 11:56:10 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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

	x = ft_isprint(c);
	y = ft_isprint(b);
	printf("%d", x);
	printf("%d", y);
}*/
