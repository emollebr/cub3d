/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:06:23 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 12:00:05 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
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

	x = ft_tolower(c);
	y = ft_tolower(b);
	printf("%d", x);
	printf("%d", y);
}*/
