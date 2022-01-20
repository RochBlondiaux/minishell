/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:09:14 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 22:36:51 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_user_input(t_app *app, char *input)
{
	char	**args;
	int		result;

	args = ft_split(input, ' ');
	result = hande_command(app, args[0], args);
	if (!result)
	{
		// TODO : remove the following line
		printf("%s%s\n", RED, COMMAND_NOT_FOUND);
		// TODO : handle environment commands (valgrind, apt, ...)
		// if no environment command is found, print not found message
		// on error output with utils/outputs#error(message)
	}
	if (result)
		add_history(input);
	free_array(args);
	free(input);
}

void	launch_engine_loop(t_app *app)
{
	char	*line;

	while (app->running)
	{
		line = readline(PROMPT_SYMBOL);
		if (ft_strlen(line) == 0)
			continue ;
		handle_user_input(app, line);
	}
}
