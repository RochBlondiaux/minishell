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

static void update_status(t_command *cmd)
{
	if (WIFEXITED(cmd->p_status))
		cmd->p_status = WEXITSTATUS(cmd->p_status);
	if (!WIFSIGNALED(cmd->p_status))
		return ;
	cmd->p_status = WTERMSIG(cmd->p_status);
}

void	execute_native(t_app *app, t_command *cmd, char *e, t_pipe *pipe)
{
	(void) app;
	if (cmd->pid == 0) {
		dup2(pipe->backup, 0);
		if (cmd->next_token == PIPE && cmd->next_cmd)
			dup2(pipe->out, STDOUT_FILENO);
		close(pipe->in);
		if (cmd->input_fd > 0)
		{
			dup2(cmd->input_fd, STDIN_FILENO);
			close(cmd->input_fd);
		}
		close(pipe->out);
		if (cmd->output_fd > 0)
			dup2(cmd->output_fd, STDOUT_FILENO);
		execve(e, get_executable_args(cmd), NULL);
		exit(1);
	}
	else {
		waitpid(cmd->pid, &cmd->p_status, 0);
		close(pipe->out);
		update_status(cmd);
		pipe->backup = pipe->in;
	}
}