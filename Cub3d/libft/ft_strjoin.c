/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:03:11 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/14 15:50:08 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"
/*
 size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*cat;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	cat = (char *)malloc(sizeof(char) * len + 1);
	if (cat == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		cat[i] = s2[j];
		i++;
		j++;
	}
	cat[i] = '\0';
	return (cat);
}
/*
#include <stdio.h>
int		main(void)
{
	char	*s1 = "Hello ";
	char	*s2 = "world!";
	
	printf("%s\n", ft_strjoin(s1, s2));
}*/
