/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:05:04 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/20 18:30:59 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

int	ft_check(char const *set, char const c)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int	trim_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0') && (ft_check(set, s1[i]) == 1))
	{
		i++;
	}
	return (i);
}

int	trim_end(char const *s1, char const *set)
{
	int	i;
	int	end;

	end = 0;
	i = (ft_strlen(s1) - 1);
	while ((i >= 0) && (ft_check(set, s1[i]) == 1))
	{
		end++;
		i--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	beg;
	unsigned int	end;
	char			*cpy;

	i = 0;
	beg = trim_start(s1, set);
	end = trim_end(s1, set);
	if (!s1)
		return (NULL);
	if (beg == ft_strlen(s1))
		return (cpy = ft_calloc(1, 1));
	cpy = ft_calloc(1, (ft_strlen(s1) - beg - end + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (beg < (ft_strlen(s1) - end))
	{
		cpy[i] = s1[beg];
		i++;
		beg++;
	}
	cpy[i] = '\0';
	return (cpy);
}
/* 
#include <stdio.h>
int main(void)
{
    char const   *str = " lorem  ipsum  dolor sit  amet";
    char const   *set = "l ";

    printf("%s\n", ft_strtrim(str, set));
} */