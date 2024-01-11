/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:58:01 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/15 11:50:08 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*tem;

	tem = s;
	i = 0;
	while (i < n)
	{
		tem[i] = c;
		i++;
	}
	return ((void *)s);
}
/*
#include <string.h>

int main () {
   char str[50];

   strcpy(str,"This is string.h library function");
   puts(str);
	
	ft_memset(str, '0', 49);
	puts(str);
}*/