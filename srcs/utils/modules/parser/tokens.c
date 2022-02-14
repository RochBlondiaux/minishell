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

static char *pri(t_token token)
{
	if (!token) return "ERROR";
	switch (token)
	{
		case LITERAL:
			return "NONE";
		case REDIRECTION:
			return "REDIR";
		case OR:
			return "OR";
		case SEMI_COLON:
			return "SEMI COLON";
		case PIPE:
			return "PIPE";
		case AND:
			return "AND";
		case AMPERSAND:
			return "AMPERSAND";
		default:
			return "?";
	}
}

static void print_tokens(t_command **commands)
{
	int i = -1;
	while (commands[++i])
	{
		printf("===== [%s] =====\n", commands[i]->name);
		printf("Last: %s\n", pri(commands[i]->previous_token));
		printf("Next: %s\n\n", pri(commands[i]->next_token));
	}
}

void parse_cmd_tokens(t_command **cmds, char *raw)
{
	size_t	i;
	size_t	j;
	t_token	c;

	i = -1;
	j = 0;
	while (raw[++i] && cmds[j])
	{
		if (is_separator(raw, i))
		{
			c = get_token(raw, i);
			cmds[j]->next_token = c;
			if (cmds[j + 1])
				cmds[j + 1]->previous_token = c;
			j++;
			if (c == OR || c == AND)
				i += 2;
			continue ;
		}
	}
	print_tokens(cmds);
}