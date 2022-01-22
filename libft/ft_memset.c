/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:29:37 by rblondia          #+#    #+#             */
/*   Updated: 2021/12/05 17:41:21 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*tmp;

	index = 0;
	tmp = (unsigned char *) s;
	while (index < n)
	{
		tmp[index] = (unsigned char) c;
		index++;
	}
	return (tmp);
}
