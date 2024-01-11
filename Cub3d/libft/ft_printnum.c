/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:48:23 by emollebr          #+#    #+#             */
/*   Updated: 2023/01/28 15:58:59 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_printnum(long long int n)
{
	char				*num;
	long long int		len;

	if (n == 0)
		return (ft_putchar_int('0'));
	if (!n)
	{
		ft_putstr_fd("(null)", 1);
		return (0);
	}
	num = ft_itoa_printf(n);
	len = ft_putstr_int(num);
	free(num);
	return (len);
}

/* int	main()
{
	int len;

	len = ft_printnum(15);
	printf("\nlen: %i\n", len);
	return 0;
} */