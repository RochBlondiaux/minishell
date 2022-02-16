/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	execute_native(t_app *app, t_command *cmd, char *e, t_pipe *pipe)
{
	(void) app;
	if (cmd->pid == 0) {
		dup2(pipe->backup, 0);
		if (cmd->next_token == PIPE && cmd->next_cmd)
			dup2(pipe->out, 1);
		close(pipe->in);
		execve(e, get_executable_args(cmd), NULL);
	}
	else {
		wait(NULL);
		close(pipe->out);
		pipe->backup = pipe->in;
	}
}