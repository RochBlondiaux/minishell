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

static void execute_parent(t_app *app, t_command *cmd, int *pipe)
{
	char	buff[2];

	if (cmd->output_path[0] || cmd->next_token == PIPE)
	{
		close(pipe[1]);
		while (read(pipe[0], &buff, 1) > 0)
		{
			buff[1] = '\0';
			cmd->output = ft_strjoin_properly(cmd->output, ft_strdup(buff));
		}
		close(pipe[0]);
		if (cmd->next_token != PIPE)
			write_in_file(app, cmd->output_path, cmd->output, cmd->appender);
	}
	else if (cmd->input[0] || cmd->previous_token == PIPE)
	{
		if (cmd->previous_cmd && cmd->previous_token == PIPE)
		{
			free(cmd->input);
			cmd->input = ft_strdup(cmd->previous_cmd->output);
		}
		close(pipe[0]);
		ft_putstr_fd(cmd->input, pipe[1]);
		close(pipe[1]);
	}
}

static void execute_child(t_command *cmd, int *pipe)
{
	if (cmd->output_path[0] || cmd->next_token == PIPE)
	{
		close(pipe[0]);
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
	}
	else if (cmd->input[0] || (cmd->previous_token == PIPE && cmd->previous_cmd))
	{
		close(pipe[1]);
		dup2(pipe[0], STDIN_FILENO);
		close(pipe[0]);
	}
}

void	execute_native(t_app *app, t_command *cmd, int *pipe, char *e)
{
	if (cmd->pid == 0)
	{
		execute_child(cmd, pipe);
		execve(e, get_executable_args(cmd), NULL);
	}
	else
		execute_parent(app, cmd, pipe);
}