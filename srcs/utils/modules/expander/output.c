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

void	expand_output(t_app *app, t_command *cmd)
{
	if (!cmd->output_path
		|| !cmd->output_path[0])
		return;
	if (cmd->appender)
		cmd->output_fd = open(cmd->output_path,
				  O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				  | S_IRGRP | S_IWGRP | S_IWUSR);
	else
		cmd->output_fd = open(cmd->output_path,
				  O_CREAT | O_RDWR | O_TRUNC, S_IRUSR
				  | S_IRGRP | S_IWGRP | S_IWUSR);
	if (cmd->output_fd <= 0)
		str_error(app, cmd->name);
}
