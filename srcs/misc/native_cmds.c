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

static t_native	*pre_check(t_command *cmd)
{
	t_native *native;

	native = create_native_cmd(cmd);
	if (!native)
		return (NULL);
	if (!native->name)
	{
		free_native_cmd(native);
		return (NULL);
	}
	native->pid = fork();
	return (native);
}

static void post_check(t_app *app, t_native *native, int *status)
{
	if (waitpid(native->pid, status, WUNTRACED | WCONTINUED) == -1)
		app->error = 1;
	else
		app->error = WEXITSTATUS(*status);
	native->exit = WEXITSTATUS(*status);
	kill(native->pid, SIGKILL);
}

// TODO : implement execute_native_command with input
// TODO : implement execute_native_command with output

t_native *execute_native_command(t_app *app, t_command *cmd)
{
	t_native	*native;
	int			status;

	native = pre_check(cmd);
	if (!native)
		return (NULL);
	if (native->pid < 0)
		str_error(app, OCCURRED_ERROR);
	else if (native->pid == 0)
	{
		execv(native->name, native->args);
	}
	post_check(app, native, &status);
	return (native);
}