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

t_native *execute_native_command(t_app *app, t_command *cmd)
{
	t_native	*native;
	int			status;

	native = create_native_cmd(cmd);
	if (!native)
		return (NULL);
	if (native->pid < 0)
		str_error(app, OCCURRED_ERROR);
	else if (native->pid == 0)
		execv(native->name, native->args);
	if (waitpid(native->pid, &status, WUNTRACED | WCONTINUED) == -1)
		app->error = 1;
	else
		app->error = WEXITSTATUS(status);
	native->exit = WEXITSTATUS(status);
	kill(native->pid, SIGKILL);
	return (native);
}