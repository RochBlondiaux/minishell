/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 15:46:43 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	native_executor(t_app *app, t_command *cmd)
{
	t_native	*native;

	native = execute_native_command(app, cmd);
	if (!native || native->pid < 0)
		return (0);
	free_native_cmd(native);
	return (1);
}

void	executor(t_app *app, t_command **commands)
{
	int			index;
	t_command	*cmd;

	index = -1;
	while (commands[++index])
	{
		cmd = commands[index];
		if (dispatch_builtin(app, cmd)
			|| native_executor(app, cmd))
			continue ;
		str_error(app, COMMAND_NOT_FOUND);
		app->last_status = 127;
		if (app->last_status != 0 && cmd->next_token == DOUBLE_PIPE)
			continue ;
	}
}
