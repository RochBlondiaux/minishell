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

int	expand_input(t_app *app, t_command *cmd)
{
	t_redir	*r;

	r = cmd->redirections;
	while (r)
	{
		if (r->type == INPUT || r->type == DELIMITER)
		{
			if (!r->path || !r->path[0] || r->path[0] == '$')
			{
				error(app, cmd->name, "ambiguous redirect");
				return (FALSE);
			}
			cmd->input_fd = open(r->path, O_RDONLY);
			if (cmd->input_fd <= 0)
			{
				error(app, r->path, "No such file or directory");
				return (FALSE);
			}
		}
		r = r->next;
	}
	return (TRUE);
}
