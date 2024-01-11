/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:06:25 by emollebr          #+#    #+#             */
/*   Updated: 2023/01/31 18:26:27 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static int	ft_check_fmt(const char *fmt, va_list ap, int i)
{
	int	sum;

	sum = 0;
	if (fmt[i + 1] == 'c')
		sum = sum + ft_putchar_int(va_arg(ap, int));
	if (fmt[i + 1] == 's')
		sum = sum + ft_putstr_int(va_arg(ap, char *));
	if (fmt[i + 1] == 'p')
		sum = sum + ft_putptr(va_arg(ap, void *));
	if (fmt[i + 1] == 'd' || fmt[i + 1] == 'i')
		sum = sum + ft_printnum(va_arg(ap, int));
	if (fmt[i + 1] == 'u')
		sum = sum + ft_putunsigned(va_arg(ap, unsigned int));
	if (fmt[i + 1] == 'x' || fmt[i + 1] == 'X')
		sum = sum + ft_puthex(va_arg(ap, unsigned int), fmt[i + 1]);
	if (fmt[i + 1] == '%')
		sum = sum + ft_putchar_int('%');
	return (sum);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	va_start(ap, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && ft_strchr("cspdiuxX%", fmt[i + 1]))
		{
			sum = sum + ft_check_fmt(fmt, ap, i);
			i++;
		}
		else
			sum = sum + ft_putchar_int(fmt[i]);
		i++;
	}
	va_end(ap);
	return (sum);
}

