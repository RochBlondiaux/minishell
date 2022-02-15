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
}

static int	execute_native_command(t_app *app, t_command *cmd)
{
	char	*executable;

	executable = get_executable(app, cmd->name);
	if (!executable)
		return (FALSE);
	if (!fork_cmd(app, cmd))
	{
		free(executable);
		return (FALSE);
	}
	if (cmd->pid == 0)
	{
		execve(executable, get_executable_args(cmd), NULL);
		exit(1);
	}
	clear_fork(cmd);
	free(executable);
	return (TRUE);
}

static void	execute_command(t_app *app, t_command *cmd)
{
	if (is_builtin(cmd))
	{
		dispatch_builtins(app, cmd);
		return ;
	}
	if (execute_native_command(app, cmd))
		return ;
	cmd->status = 127;
	error(app, cmd->name, COMMAND_NOT_FOUND);
}

void	executor(t_app *app, t_command **cmds)
{
	int	i;

	i = -1;
	init_commands(cmds);
	while (cmds[++i])
	{
		execute_command(app, cmds[i]);
		app->last_exit = cmds[i]->status;
	}
}
