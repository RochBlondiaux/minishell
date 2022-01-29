/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 14:36:46 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	array_length(void *array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(void *array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
	}
	free(array);
}
