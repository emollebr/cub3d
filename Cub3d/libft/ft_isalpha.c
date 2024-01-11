/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:04:50 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/08 11:55:50 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	if (c >= 'a' && c <= 'z')
	{
		return (2);
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

	x = ft_isalpha(c);
	y = ft_isalpha(b);
	printf("%d", x);
	printf("%d", y);
}*/
