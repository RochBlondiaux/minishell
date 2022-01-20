/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:18:27 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 21:22:25 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	array_length(char **a)
{
	size_t	l;

	l = 0;
	while (a[l++])
		;
	return (l);
}

void	free_array(char **a)
{
	size_t	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}
