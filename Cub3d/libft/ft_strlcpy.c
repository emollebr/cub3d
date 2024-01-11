/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:59:06 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/15 15:36:53 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (src[length] != '\0')
	{
		length++;
	}
	if (size < 1)
		return (length);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	str[] = "bubble";
	char	rts[] = "tea";

	char	str1[] = "bubble";
	char	rts1[] = "tea";
	int	size = 2;
	int a = ft_strlcpy(str, rts, size);
	unsigned int	b = strlcpy(str1, rts1, size);
	printf("%d\n",a);
	printf("%d", b);
	return (0);
}*/