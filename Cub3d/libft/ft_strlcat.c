/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:59:46 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:27:15 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = ft_strlen(dst);
	if (size - 1 < j || size == 0)
		return (ft_strlen(src) + size);
	while (src[i] != '\0' && j + i < (size - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[i + j] = '\0';
	return (ft_strlen(src) + j);
}
/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char	dest[11] = "a";
	char	src[] = "lorem";

	char    dest1[10] = "hello";
	char    src1[] = "bubble";
	size_t	a = 15;

	printf("%ld\n", ft_strlcat(dest, src, a));
	printf("%ld", ft_strlcat(dest1, src1, a));
	return (0);
} */