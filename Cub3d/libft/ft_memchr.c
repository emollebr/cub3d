/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:28:27 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/20 18:38:26 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (i < n)
	{
		if (((char *)s)[i] == (char)c)
		{
			ret = &((char *)s)[i];
			return ((void *)ret);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "miiiiiiiau";
	char	*ptr = (ft_memchr(str, 'a', 20));

	printf("%s", ptr);
}*/