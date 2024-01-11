/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:42:56 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/15 11:42:28 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tem;

	tem = s;
	i = 0;
	while (i < n)
	{
		tem[i] = '\0';
		i++;
	}
}
/*
#include <string.h>

int main () {
   char str[50];

   strcpy(str,"This is string.h library function");
   puts(str);
	
	ft_bzero(str, 4);
	puts(str);
}*/
