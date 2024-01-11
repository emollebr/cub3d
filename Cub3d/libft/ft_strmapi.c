/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:26:52 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/20 18:25:11 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*alt_s;

	alt_s = ft_calloc(1, ft_strlen(s) + 1);
	if (alt_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		alt_s[i] = (*f)(i, s[i]);
		i++;
	}
	alt_s[i] = '\0';
	return (alt_s);
}
/*
char	ft_upper(unsigned int i, char c)
{
	if (i < 10000000)
	{
		if (c >= 'a' && c <= 'z')
			c = c - 32;
	}
	return (c);
}

#include <stdio.h>
int main()
{
	char *s = "hello";
	char *mapped = ft_strmapi(s, &ft_upper);
	printf("%s\n", mapped); // Prints "HELLO"
	free(mapped);
}*/
