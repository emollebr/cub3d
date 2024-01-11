/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:57:36 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:37:57 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return ((void *)dest);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
    char    dest[50] = "Ciaoo world";
    char    dest1[50] = "Ciaoo world";
    char    src[50] = "Hello world";

    char    *p = memcpy(dest, src, 5);
    printf("%s\n", p); 
    p = ft_memcpy(dest1, src, 5);
    printf("%s", p);
}*/