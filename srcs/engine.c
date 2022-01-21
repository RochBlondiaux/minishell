/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:09:14 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/21 11:31:28 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_command(char **args)
{
	char	*path;
	pid_t	sub;

	path = get_program_path(args[0]);
	if (!path)
		return (FALSE);
	sub = sub_process();
	if (sub == 0)
	{
		execv(path, &args[0]);
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

	args = ft_split(input, ' ');
	result = hande_command(app, args[0], args);
	if (!result)
	{
		result = execute_command(args);
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
		if (app->error)
			line = readline(ERROR_PROMPT_SYMBOL);
		else
			line = readline(PROMPT_SYMBOL);
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
