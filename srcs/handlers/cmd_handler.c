/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:10:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/22 18:16:57 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_normal_cmd(t_app *app, char *path, char **args)
{
	int		status;

	app->sub = sub_process();
	if (app->sub == 0)
		execv(path, args);
	waitpid(app->sub, &status, 0);
	kill(app->sub, SIGKILL);
	app->error = WEXITSTATUS(status);
}

static int	handle_special_cmd(t_app *app, char *input, int *fd)
{
	int	status;

	close(fd[0]);
	write(fd[1], input, ft_strlen(input));
	close(fd[1]);
	waitpid(app->sub, &status, 0);
	return (status);
}

static void	execute_special_cmd(t_app *app, char *path,
								char *name, char *input)
{
	int		status;
	int		fd[2];
	char	*args[2];

	if (pipe(fd) == -1)
	{
		str_error(app, "pipe error");
		return ;
	}
	args[0] = name;
	args[1] = NULL;
	app->sub = sub_process();
	if (app->sub == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execv(path, args);
	}
	else
		status = handle_special_cmd(app, input, fd);
	kill(app->sub, SIGKILL);
	app->error = WEXITSTATUS(status);
}

int	handle_env_cmd(t_app *app, char *name,
					char **args, char *input)
{
	char	*path;

	if (input && !input[0])
		return (-1);
	path = get_program_path(name);
	if (!path)
		return (FALSE);
	if (!input)
		execute_normal_cmd(app, path, args);
	else
		execute_special_cmd(app, path, name, input);
	free(path);
	free(input);
	return (1);
}
