/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:56:07 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/21 14:47:36 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

static char	*substrsplit(char const *s, char c, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
		return (NULL);
	while (s[i] != '\0' && s[start + i] != (unsigned char)c && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static size_t	count_elems(char const *s, char c)
{
	size_t	i;
	size_t	elems;

	elems = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == (unsigned char)c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			elems++;
		while (s[i] != (unsigned char)c && s[i] != '\0')
			i++;
	}
	return (elems);
}

static size_t	substrlen(char const *s, char c, size_t i)
{	
	size_t	l;

	l = 0;
	while (s[i + l] != '\0' && s[i + l] != (unsigned char)c)
		l++;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	size_t		i;
	size_t		e_len;
	size_t		e_index;

	i = 0;
	e_index = 0;
	e_len = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc((count_elems(s, c) * 8 + 1));
	if (split == NULL)
		return (NULL);
	while (e_index < (count_elems(s, c)))
	{	
		while (s[i] == (unsigned char)c)
			i++;
		e_len = substrlen(s, c, i);
		split[e_index] = substrsplit(s, c, i, e_len + 1);
		e_index++;
		i = i + e_len;
	}
	return (split);
}
/* 
int	main(void)
{
	char	*s = "\0aa\0bbb";
	char	**print;
	size_t	i;
	
	printf("%zu\n", count_elems(s, '\0'));
	i = 0;
	print = ft_split(s, '\0');
	while (i < count_elems(s, '\0'))
	{
		printf("%s\n", print[i]);
		i++;
	}
} */
