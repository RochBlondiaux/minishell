/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_native	*pre_check(t_app *app, t_command *cmd)
{
	t_native	*native;

	native = create_native_cmd(cmd);
	if (!native)
		return (NULL);
	if (!native->name)
	{
		free_native_cmd(native);
		return (NULL);
	}
	native->pid = fork();
	if (native->pid == -1)
	{
		str_error(app, OCCURRED_ERROR);
		return (NULL);
	}
	return (native);
}

static void	post_check(t_app *app, t_native *native)
{
	if (waitpid(native->pid, &native->status, WUNTRACED | WCONTINUED) == -1)
		app->error = 1;
	else
		app->error = WEXITSTATUS(native->status);
	native->exit = WEXITSTATUS(native->status);
	kill(native->pid, SIGKILL);
	app->last_status = WEXITSTATUS(native->status);
}

static void	execute_child(t_command *cmd, int *fd)
{
	if (cmd->output_path[0])
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (cmd->input[0])
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	execute_parent(t_command *cmd, t_app *app, int *fd)
{
	char	buff[2];

	if (cmd->output_path[0])
	{
		close(fd[1]);
		while (read(fd[0], &buff, 1) > 0)
		{
			buff[1] = '\0';
			cmd->output = ft_strjoin_properly(cmd->output, ft_strdup(buff));
		}
		close(fd[0]);
		write_output(app, cmd);
	}
	else if (cmd->input[0])
	{
		close(fd[0]);
		ft_putstr_fd(cmd->input, fd[1]);
		close(fd[1]);
	}
}

t_native	*execute_native_command(t_app *app, t_command *cmd)
{
	t_native	*native;
	int			fd[2];

	if (pipe(fd) == -1)
		return (NULL);
	native = pre_check(app, cmd);
	if (!native)
		return (NULL);
	if (native->pid == 0)
	{
		execute_child(cmd, fd);
		execv(native->name, native->args);
	}
	else
		execute_parent(cmd, app, fd);
	post_check(app, native);
	return (native);
}
