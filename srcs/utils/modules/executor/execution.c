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
		// TODO: fix this code (working for "cat < LICENSE.md" but not for "cat < LICENSE.md | wc -l")
		//if (cmd->input[0])
		//	dup2(pipe->in, STDIN_FILENO);
		if (cmd->next_token == PIPE && cmd->next_cmd)
			dup2(pipe->out, STDOUT_FILENO);
		execve(e, get_executable_args(cmd), NULL);
		close(pipe->in);
		exit(1);
	}
	else {
		// TODO: fix this code (working for "cat < LICENSE.md" but not for "cat < LICENSE.md | wc -l")
		// if (cmd->input[0])
		//	ft_putstr_fd(cmd->input, pipe->out);
		wait(NULL);
		close(pipe->out);
		pipe->backup = pipe->in;
	}
}