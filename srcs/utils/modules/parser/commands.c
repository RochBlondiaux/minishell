/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

size_t	count_commands(char *input)
{
	size_t	index;
	size_t	count;

	index = -1;
	count = 1;
	while (input[++index])
	{
		if (is_separator(input, index))
			count++;
	}
	return (count);
}

char	**parse_raw_commands(char *raw)
{
	char	**cmds;
	size_t	index;
	size_t	j;
	size_t	s;

	cmds = malloc(sizeof(char *) * (count_commands(raw) + 1));
	if (!cmds)
		return (NULL);
	index = 0;
	j = 0;
	while (j < count_commands(raw))
	{
		while (is_separator(raw, index))
			index ++;
		s = strchr_separator(&raw[index]);
		cmds[j++] = ft_substr(raw, index, s);
		index += s;
		if (index >= ft_strlen(raw))
			break ;
	}
	cmds[j] = NULL;
	return (cmds);
}
