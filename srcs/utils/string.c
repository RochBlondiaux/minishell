/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	j = i;
	while (src[i - j])
	{
		dst[i] = src[i - j];
		i++;
	}
	dst[i] = '\0';
}

static void	replace_utils(char **destptr, char **sentence)
{
	**destptr = **sentence;
	(*destptr)++;
	(*sentence)++;
}

char	*ft_replace(char *sentence, char *find, char *replace)
{
	char	*dest;
	char	*destptr;

	dest = malloc(ft_strlen(sentence) - ft_strlen(find)
			+ ft_strlen(replace) + 1);
	if (!dest)
		return (sentence);
	destptr = dest;
	*dest = 0;
	while (*sentence)
	{
		if (!ft_strncmp(sentence, find, ft_strlen(find)))
		{
			ft_strcat(destptr, replace);
			sentence += ft_strlen(find);
			destptr += ft_strlen(replace);
		}
		else
			replace_utils(&destptr, &sentence);
	}
	*destptr = 0;
	free(find);
	free(replace);
	return (dest);
}
