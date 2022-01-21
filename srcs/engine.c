/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:09:14 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 14:14:04 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_command(char *name, char **args)
{
	char	*path;
	pid_t	sub;

	path = get_program_path(name);
	if (!path)
		return (FALSE);
	sub = sub_process();
	if (sub == 0)
	{
		execv(path, args);
	}
	waitpid(sub, 0, 0);
	kill(sub, SIGKILL);
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
	result = hande_command(app, command, &args[1]);
	if (!result)
	{
		result = execute_command(command, &args[0]);
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
			break;
		else if (ft_strlen(line) == FALSE)
		{
			app->error = TRUE;
			continue ;
		}
		handle_user_input(app, line);
	}
}
