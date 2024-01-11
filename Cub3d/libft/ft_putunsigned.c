/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:10:36 by emollebr          #+#    #+#             */
/*   Updated: 2023/01/17 11:25:01 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static int	ft_get_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int nbr)
{
	int		len;
	char	*str;

	len = ft_get_len(nbr);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (nbr != 0)
	{
		str[len - 1] = nbr % 10 + 48;
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

int	ft_putunsigned(unsigned int nbr)
{
	char	*num;
	int		len;

	if (nbr == 0)
		return (ft_putchar_int('0'));
	else
	{
		num = ft_uitoa(nbr);
		ft_putstr_fd(num, 1);
		len = ft_strlen(num);
		free(num);
		return (len);
	}
}
