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

size_t	count_commands(char **args)
{
	size_t	index;
	size_t	count;

	index = -1;
	count++;
	while (args[++index])
	{
		if (is_separator(args[index]))
			count++;
	}
	return (count);
}

char	**parse_raw_commands(char *raw)
{
	char	**cmds;
	char	*current;
	size_t	index;
	size_t	j;

	cmds = malloc(sizeof(char *) * (count_commands(args) + 1));
	if (!cmds)
		return (NULL);
	index = -1;

	return (cmds);
}
