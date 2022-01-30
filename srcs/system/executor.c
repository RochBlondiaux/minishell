/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:18 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_env_command(t_app *app, t_command *cmd)
{
	(void) app;
	(void) cmd;
	return (FALSE);
}

void executor(t_app *app, t_command **commands)
{
	int			index;
	t_command	*cmd;

	index = -1;
	while (commands[++index])
	{
		cmd = commands[index];
		if (dispatch_builtin(app, cmd))
			continue ;
		if (execute_env_command(app, cmd))
			continue ;
		str_error(app, COMMAND_NOT_FOUND);
	}
}