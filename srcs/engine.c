/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:09:14 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 14:59:48 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**process_redirections(t_app *app, char **args)
{
	size_t	i;

	i = -1;
	while (args[++i])
	{
		if (args[i] && ft_strlen(args[i]) == 1)
		{
			if (args[i][0] == '<')
				handle_input_redirection(app, &args[i + 1]);
			else if (args[i][0] == '>')
				handle_output_redirection(app, &args[i + 1]);
		}
	}
	return (args);
}

static int	execute_command(t_app *app, char *name, char **args)
{
	char	*path;

	path = get_program_path(name);
	if (!path)
		return (FALSE);
	app->sub = sub_process();
	if (app->sub == 0)
		execv(path, args);
	waitpid(app->sub, 0, 0);
	kill(app->sub, SIGKILL);
	free(path);
	return (1);
}

static void	handle_user_input(t_app *app, char *input)
{
	char	**args;
	int		result;
	char	*command;

	args = ft_split(input, ' ');
	command = args[0];
	args = process_env_vars(args);
	args = process_redirections(app, args);
	result = hande_command(app, command, &args[1]);
	if (!result)
	{
		result = execute_command(app, command, &args[0]);
		if (!result)
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
