/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:23:15 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:56:49 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (void *)malloc(nmemb * size);
	if (!ret)
		return (NULL);
	while (i < nmemb * size)
	{
		ret[i] = '\0';
		i++;
	}
	return ((void *)ret);
}
/*
int	main(void)
{
	ft_calloc(7, 4);
	printf("%s", 
}*/