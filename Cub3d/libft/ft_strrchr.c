/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:31:02 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/20 18:37:59 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ret;
	int			i;

	i = 0;
	ret = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			ret = &s[i];
		i++;
	}
	if (s[i] == (char)c)
	{
		ret = &s[i];
	}
	return ((char *) ret);
}
/*
#include <stdio.h>

int main(void)
{
    const char  *s = "Hello world";
    int c = 'o';
    char    *p;

    p = ft_strrchr(s, c);
    printf("%s", p);            
}*/