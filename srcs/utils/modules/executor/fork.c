/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	fork_cmd(t_app *app, t_command *cmd)
{
	cmd->pid = fork();
	cmd->p_status = 0;
	if (cmd->pid == -1)
	{
		error(app, cmd->name, FORK_ERROR);
		return (FALSE);
	}
	return (TRUE);
}

void	clear_fork(t_app *app, t_command *cmd)
{
	(void) app;
	signal(SIGINT, SIG_IGN);
	waitpid(cmd->pid, &cmd->p_status, WUNTRACED | WCONTINUED);
	if (WIFEXITED(cmd->p_status))
		cmd->p_status = WEXITSTATUS(cmd->p_status);
	if (WIFSIGNALED(cmd->p_status))
		cmd->p_status = WCOREDUMP(cmd->p_status);
}
