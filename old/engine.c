/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:09:14 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:15 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*process_redirections(t_app *app, char **args)
{
	char	*input;
	size_t	i;

	i = -1;
	while (args[++i])
	{
		if (args[i] && ft_strlen(args[i]) == 1)
		{
			if (args[i][0] == '<')
			{
				input = handle_input_redirection(app, &args[i + 1]);
				if (input)
					return (input);
				return ("");
			}
			else if (args[i][0] == '>')
				handle_output_redirection(app, &args[i + 1]);
		}
	}
	return (NULL);
}

static void	handle_user_input(t_app *app, char *input)
{
	char	**args;
	int		result;
	char	*command;
	char	*redirection_input;

	args = ft_split(input, ' ');
	command = args[0];
	args = process_env_vars(args);
	redirection_input = process_redirections(app, args);
	result = hande_command(app, command, &args[1]);
	if (!result)
	{
		result = handle_env_cmd(app, command,
				&args[0], redirection_input);
		if (result == 0)
			str_error(app, COMMAND_NOT_FOUND);
	}
	add_history(input);
	free_array(args);
	free(input);
}

void	launch_engine_loop(t_app *app)
{
	char	*line;

	while (app->running)
	{
		line = readline(get_prompt_symbol(app));
		app->error = FALSE;
		if (!line)
			break ;
		else if (ft_strlen(line) == FALSE)
		{
			app->error = TRUE;
			continue ;
		}
		handle_user_input(app, line);
	}
}