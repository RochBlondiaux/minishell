/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:53:40 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 15:43:54 by lfilloux         ###   ########.fr       */
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
	expand(app, commands);
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
		{
			free(line);
			continue ;
		}
		add_history(line);
		free(line);
	}
}
