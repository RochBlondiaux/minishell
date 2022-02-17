/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_commands(t_command **cmds)
{
	int	i;

	i = -1;
	cmds[0]->previous_cmd = NULL;
	while (cmds[++i])
	{
		if (cmds[i - 1])
			cmds[i]->previous_cmd = cmds[i - 1];
		if (cmds[i + 1])
			cmds[i]->next_cmd = cmds[i + 1];
	}
	cmds[i - 1]->next_cmd = NULL;
}

static int	execute_native_command(t_app *app, t_command *cmd, t_pipe *pipe)
{
	char	*executable;

	executable = get_executable(app, cmd, cmd->name);
	if (!executable)
		return (FALSE);
	if (!executable[0])
	{
		free(executable);
		return (-1);
	}
	if (!fork_cmd(app, cmd))
	{
		free(executable);
		return (FALSE);
	}
	execute_native(app, cmd, executable, pipe);
	free(executable);
	return (TRUE);
}

static void	execute_command(t_app *app, t_command *cmd, t_pipe *pipe)
{
	int	ret;

	if (is_builtin(cmd))
	{
		dispatch_builtins(app, cmd);
		return ;
	}
	ret = execute_native_command(app, cmd, pipe);
	if (ret != FALSE)
	{
		if (ret == -1)
			return ;
		cmd->status = cmd->p_status;
		return ;
	}
	cmd->status = 127;
	error(app, cmd->name, COMMAND_NOT_FOUND);
}

void	executor(t_app *app, t_command **cmds)
{
	int	i;
	t_pipe	*pipe;

	i = -1;
	init_commands(cmds);
	pipe = init_pipeline(app);
	if (!pipe)
		return ;
	while (cmds[++i])
	{
		if (cmds[i]->name && !cmds[i]->name[0])
			continue ;
		execute_command(app, cmds[i], pipe);
		app->last_exit = cmds[i]->status;
		app->exit = app->last_exit != 0;
		update_pipeline(app, pipe);
	}
	free(pipe);
}
