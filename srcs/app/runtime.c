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
//	char		**args;
//	t_command	**commands;
	t_token		*tokens;
	int			result;

	result = 0;
	tokens = lexer(app, input, &result);
	if (!tokens)
		return (result);
//	commands = parse(args);
//	expand(app, commands);
//	executor(app, commands);
//	free_commands(commands);*/
	return (TRUE);
}
