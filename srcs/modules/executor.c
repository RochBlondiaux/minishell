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

static void	execute_command(t_app *app, t_command *cmd)
{
	if (is_builtin(cmd))
		dispatch_builtins(app, cmd);
}

void	executor(t_app *app, t_command **cmds)
{
	int	i;

	i = -1;
	init_commands(cmds);
	while (cmds[++i])
		execute_command(app, cmds[i]);
}
