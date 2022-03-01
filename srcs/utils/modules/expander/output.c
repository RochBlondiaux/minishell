/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	open_fd(t_redir *r, t_command *cmd)
{
	if (r->type == APPENDER)
		cmd->output_fd = open(r->path,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	else
		cmd->output_fd = open(r->path,
				O_CREAT | O_RDWR, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
}

int	expand_output(t_app *app, t_command *cmd)
{
	t_redir	*r;

	r = cmd->redirections;
	while (r)
	{
		if (r->type == OUTPUT || r->type == APPENDER)
		{
			if (!r->path || !r->path[0] || r->path[0] == '$')
			{
				error(app, cmd->name, "ambiguous redirect");
				return (FALSE);
			}
			open_fd(r, cmd);
			if (cmd->output_fd <= 0)
			{
				error(app, r->path, "No such file or directory");
				return (FALSE);
			}
		}
		r = r->next;
	}
	return (TRUE);
}
