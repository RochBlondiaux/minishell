/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:36:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	get_token(char *a)
{
	if (ft_strcmp(a, "|"))
		return (PIPE);
	if (ft_strcmp(a, "||"))
		return (DOUBLE_PIPE);
	if (ft_strcmp(a, "&"))
		return (AMPERSAND);
	if (ft_strcmp(a, "&&"))
		return (DOUBLE_AMPERSAND);
	if (ft_strcmp(a, ";"))
		return (SEMICOLON);
	return (NONE);
}

void	parse_tokens(t_command **commands, char **args)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	commands[0]->previous_token = NONE;
	while (args[++i])
	{
		if (get_token(args[i]) != NONE)
		{
			commands[j]->next_token = get_token(args[i]);
			commands[j + 1]->previous_token = get_token(args[i]);
			j++;
		}
	}
	commands[j]->next_token = NONE;
}
