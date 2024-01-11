/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:44:25 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:46:31 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (n == 0)
		return ((void *)dest);
	else if ((void *)src > (void *)dest)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
		return ((void *)dest);
	}
	else if (((void *)dest > (void *)src) && n > 0)
	{
		i = n;
		while (i > 0)
		{
			((char *)dest)[i - 1] = ((char *)src)[i - 1];
			i--;
		}
		return ((void *)dest);
	}
	return ((void *)dest);
}
/* 
#include <stdio.h>
#include <string.h>
int main(void)
{
	    char    small[] = "lorem ipsum dolor sit amet";
    char    *big;

    big = small + 1;
    char    *p = ft_memmove(small, big, 8);
    printf("%s\n", p);
} */