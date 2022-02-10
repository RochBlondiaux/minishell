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

size_t	count_commands(char *args)
{
	size_t	index;
	size_t	count;

	index = -1;
	count = 0;
	while (args[++index])
	{
		if (is_separator(&args[index]))
			count++;
	}
	return (count);
}

char	 **parse_raw_commands(char *raw)
{
	char	**cmds;
	size_t	index;
	size_t	j;

	cmds = malloc(sizeof(char *) * (count_commands(raw) + 1));
	if (!cmds)
		return (NULL);
	index = -1;
	j = -1;
	while (raw[++index])
	{
		if (strchr_separator(&raw[index]) == 0)
			continue ;
		cmds[++j] = ft_substr(raw, index,  strchr_separator(&raw[index]));
		index += strchr_separator(&raw[index]);
		cmds[j] = ft_strtrim(cmds[j], " ");
	}
	cmds[++j] = NULL;
	return (cmds);
}
