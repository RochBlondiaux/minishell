/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	replace_utils(char **destptr, char **sentence)
{
	**destptr = **sentence;
	(*destptr)++;
	(*sentence)++;
}

char	*replace_str(char *sentence, char *find, char *replace)
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
