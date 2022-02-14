/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_cmds(t_command **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i])
	{
		printf("========[ %s ]========\n", cmds[i]->name);
		size_t j = -1;
		while (cmds[i]->args[++j])
			printf("#%zu: %s\n", j, cmds[i]->args[j]);
		printf("\n");
	}
}

int	runtime(t_app *app, char *input)
{
	t_token		*tokens;
	int			result;
	t_command	**commands;

	result = 0;
	tokens = lexer(app, input, &result);
	if (!tokens)
		return (FALSE);
	result = syntaxer(input, tokens);
	if (!result)
	{
		str_error(app, SYNTAX_ERROR);
		return (FALSE);
	}
	commands = parse(input);
//	expand(app, commands);
	print_cmds(commands);
	//	executor(app, commands);
	free_command_map(commands);
	return (TRUE);
}
