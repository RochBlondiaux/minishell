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

#include "../../includes/minishell.h"

size_t	array_length(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**sub_array(char **array, size_t start, size_t length)
{
	size_t	index;
	char	**new;

	if (start >= length || length > array_length(array))
		return (NULL);
	index = start - 1;
	new = malloc(sizeof (char *) * (length - start));
	if (!new)
		return (NULL);
	while (array[++index] && index < length)
		new[index - start] = ft_strdup(array[index]);
	return (new);
}
