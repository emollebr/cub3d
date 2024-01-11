/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:48:23 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:35:22 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static int	count_digits(int n)
{
	int	dig;
	int	str_len;

	if (n < 0)
		n = n * -1;
	str_len = 10;
	dig = 1000000000;
	while (str_len > 0)
	{
		if (n / dig >= 1)
			break ;
		dig = dig / 10;
		str_len--;
	}
	return (str_len);
}

int	if_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*corner_case(int n, char *str)
{
	if (n == 0)
	{
		str = ft_calloc(1, 2);
		str[0] = '0';
		str[1] = '\0';
	}
	else if (n == -2147483648)
		str = ft_strdup("-2147483648");
	return (str);
}

char	*loop(char *str, int len, int n)
{
	while (len > 0 && str[len - 1] != '-')
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	str = NULL;
	if (n == 0 || n == -2147483648)
	{
		str = corner_case(n, str);
		return (str);
	}
	len = count_digits(n) + if_neg(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (if_neg(n) == 1)
	{
		n = n * (-1);
		str[0] = '-';
	}
	return (loop(str, len, n));
}
/* 
int	main()
{
	printf("%s\n", ft_itoa(-834875));
	char *s = ft_itoa(-834875);
	int	i;
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
} */