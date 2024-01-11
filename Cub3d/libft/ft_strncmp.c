/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:07:18 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/14 18:36:21 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n && s1[index] != '\0'
		&& s2[index] != '\0')
	{
		if (s1[index] != s2[index])
			break ;
		index++;
	}
	if (index < n)
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	x;
	char	 org[4] = "t\2";
	char	 com[4] = "t\0";

	x = ft_strncmp(org, com, 3);
	printf("%d", x);
	printf("%s", "\n");
}  */
