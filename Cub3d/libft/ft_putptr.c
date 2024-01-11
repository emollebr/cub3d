/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:01:30 by emollebr          #+#    #+#             */
/*   Updated: 2023/01/13 15:01:32 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static void	ft_printptr(size_t adr, char fmt)
{
	if (adr >= 16)
	{
		ft_printptr(adr / 16, fmt);
		ft_printptr(adr % 16, fmt);
	}
	else
	{
		if (adr <= 9)
			ft_putchar_fd(adr + '0', 1);
		else
		{
			if (fmt == 'x')
				ft_putchar_fd(adr - 10 + 'a', 1);
			if (fmt == 'X')
				ft_putchar_fd(adr - 10 + 'A', 1);
		}
	}
}

int	ft_putptr(void *ptr)
{
	size_t	adr;
	int		len;

	len = 2;
	adr = (size_t)ptr;
	if (ptr == NULL || ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	ft_printptr(adr, 'x');
	while (adr > 0)
	{
		adr = adr / 16;
		len++;
	}
	return (len);
}
/* 
int main()
{
	int	*p = 0;
	int	m = 50;
	int	l;

	m = ft_putptr(p);
	l = printf("%p", p);
	printf("\n%d", l);
	 ft_putptr(p);
	ft_puthex(m, 'x');
	printf("\n%p%d", p, m); 
} */
