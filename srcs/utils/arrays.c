/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
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

char	**add_array_element(char **array, char *element)
{
	size_t	index;
	char	**a;

	a = malloc(sizeof(char *) * (array_length(array) + 2));
	index = -1;
	a[0] = ft_strdup(element);
	while (array[++index])
		a[index + 1] = ft_strdup(array[index]);
	a[index + 1] = NULL;
	return (a);
}
