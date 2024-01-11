/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:47:47 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/20 18:36:29 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*ret;
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			ret = &s[i];
			return ((char *)ret);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		ret = &s[i];
		return ((char *)ret);
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*s = "Hello world";
	int	c = '\0';
	char	*p;

	p = ft_strchr(s, c);
	printf("%c", (p[0] + 48)); 
}*/
