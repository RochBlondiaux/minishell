/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:22 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 14:39:00 by lfilloux         ###   ########.fr       */
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

char	*g(enum e_token token)
{
	switch (token)
	{
		case PIPE:
			return "PIPE";
		case SEMICOLON:
			return "SEMICOLON";
		case AMPERSAND:
			return "AMPERSAND";
		case DOUBLE_AMPERSAND:
			return "DOUBLE_AMPERSAND";
		case DOUBLE_PIPE:
			return "DOUBLE_PIPE";
		default:
			return "NONE";
	}
}

void	executor(t_app *app, t_command **commands)
{
	int			index;
	t_command	*cmd;

	index = -1;
	while (commands[++index])
	{
		cmd = commands[index];
		printf("PREVIOUS : %s\nNEXT : %s\n %d\n", g(cmd->previous_token), g(cmd->next_token), index);
		if (cmd->next_token == NONE)
		{
			if (dispatch_builtin(app, cmd)
				|| native_executor(app, cmd))
				continue ;
		}
		else if (cmd->next_token == DOUBLE_AMPERSAND && cmd->next)
		{
			if (dispatch_builtin(app, cmd)
				|| native_executor(app, cmd))
				continue ;
		}
		str_error(app, COMMAND_NOT_FOUND);
		app->last_status = 127;
	}
}
