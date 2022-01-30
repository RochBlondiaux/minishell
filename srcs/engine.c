/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:15 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	runtime(t_app *app, char *input)
{
	char		**args;
	t_command	**commands;
	int			result;

	result = 0;
	args = lexer(app, input, &result);
	if (!args)
		return (result);
	commands = parse(args);
	if (!commands)
		return (-1);
	expand(commands);
	executor(app, commands);
	free_commands(commands);
	return (TRUE);
}

void	start_engine(t_app *app)
{
	char	*line;
	int		rv;

	while (app->running)
	{
		line = readline(get_prompt_symbol(app));
		app->error = FALSE;
		rv = runtime(app, line);
		if (rv == -2)
			break ;
		if (rv == -1)
			continue ;
		runtime(app, line);
		if (app->error == FALSE)
			add_history(line);
		free(line);
	}
}