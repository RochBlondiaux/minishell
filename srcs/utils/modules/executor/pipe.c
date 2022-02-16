/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	*init_pipeline(t_app *app, t_command *cmd)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
	{
		cmd->status = 1;
		return (NULL);
	}
	if (pipe(fd) == -1)
	{
		cmd->status = 1;
		error(app, "-minishell", PIPE_ERROR);
		return (NULL);
	}
	return (fd);
}


