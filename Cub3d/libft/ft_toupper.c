/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:06:40 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 12:00:11 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

/*#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	c = 'A';
	int	b = '!';
	int	x;
	int	y;

	x = ft_toupper(c);
	y = ft_toupper(b);
	printf("%d", x);
	printf("%d", y);
}*/
