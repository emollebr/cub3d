/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:05:50 by emollebr          #+#    #+#             */
/*   Updated: 2023/01/17 11:24:57 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_putstr_int(char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[count] != '\0')
		count++;
	return (write(1, s, count));
}
/*
int	main(void)
{
	char	* str1;

	str1 = "hello";
	ft_putstr(str1);
	return (0);
}*/
