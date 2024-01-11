/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:13:40 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:27:56 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	ptr = ft_calloc((ft_strlen(s) + 1), 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int main(void)
{
    char *s1 = "Striiing";
    char *s2 = ft_strdup(s1);
	printf("%s\n", s2);
    printf("%d\n", strcmp(s1, s2));
	char *t1 = "Strooong";
	char *t2 = strdup(t1);
	printf("%s\n", t2);
	printf("%d\n", strcmp(t1, t2));

    free(s2);
	free(t2); 
}*/
