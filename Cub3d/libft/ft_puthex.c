/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:10:27 by emollebr          #+#    #+#             */
/*   Updated: 2023/01/17 11:24:49 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static void	ft_printhex(unsigned int num, const char fmt)
{
	if (num >= 16)
	{
		ft_printhex(num / 16, fmt);
		ft_printhex(num % 16, fmt);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd(num + '0', 1);
		else
		{
			if (fmt == 'x')
				ft_putchar_fd(num - 10 + 'a', 1);
			if (fmt == 'X')
				ft_putchar_fd(num - 10 + 'A', 1);
		}
	}
}

int	ft_puthex(unsigned int num, char fmt)
{
	int	len;

	len = 0;
	if (num == 0)
		return (write(1, "0", 1));
	if (!num)
		return (ft_putstr_int("(null)"));
	ft_printhex(num, fmt);
	while (num > 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}
/* 
int	main()
{
	printf("\n%i", ft_puthex(16, 'x'));
} */
