/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:25:54 by sclam             #+#    #+#             */
/*   Updated: 2021/10/15 15:31:42 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;

	if (!lst || !f)
		return (0);
	tmp = ft_lstnew(f(lst->content));
	if (tmp == NULL)
		return (0);
	while (lst)
	{
		lst = lst->next;
		if (lst == NULL)
			break ;
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
		{
			ft_lstclear(&tmp, del);
			return (0);
		}
		ft_lstadd_back(&tmp, new);
	}
	return (tmp);
}
