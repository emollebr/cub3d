/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:31:05 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/14 17:21:05 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] != '\0')
	{
		ptr = &s[i];
		(*f)(i, ptr);
		i++;
	}
}
/* void    ft_toupper(unsigned int i, char *c)
{
    if (i != 100000000)
    {
        if (*c >= 'a' && *c <= 'z')
            *c = *c - 32;
    }
}
#include <stdio.h>
int main()
{
    char *s = "hello";
    
	ft_striteri(s, &ft_upper);
    printf("%s\n", s); // Prints "HELLO"
}
 */