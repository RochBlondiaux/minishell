/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:03:58 by rblondia          #+#    #+#             */
/*   Updated: 2021/11/09 17:09:31 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*thelist;

	thelist = malloc(sizeof(t_list));
	if (!thelist)
		return (NULL);
	thelist->content = content;
	thelist->next = NULL;
	return (thelist);
}
