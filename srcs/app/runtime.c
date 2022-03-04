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
		app->last_exit = 2;
		return (FALSE);
	}
	input = expand_env_vars(app, input);
	if (ft_strchr(input, '*'))
		reset_str(&input, expand_wildcards(app, input));
	commands = parse(input);
	if (expand(app, commands))
		executor(app, commands);
	free_command_map(commands);
	return (TRUE);
}
