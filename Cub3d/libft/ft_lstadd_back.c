/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:06:29 by emollebr          #+#    #+#             */
/*   Updated: 2022/12/20 16:18:55 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*old;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	old = ft_lstlast(*lst);
	old->next = new;
	return ;
}
