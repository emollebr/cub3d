/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:05:37 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 11:55:58 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	c = 'A';
	int	b = 128;
	int	x;
	int	y;

	x = ft_isascii(c);
	y = ft_isascii(b);
	printf("%d\n", x);
	printf("%d", y);
}*/
