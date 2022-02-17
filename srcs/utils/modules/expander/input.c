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

void	expand_input(t_app *app, t_command *cmd)
{
	if (!cmd->input_path
		|| !cmd->input_path[0])
		return;
	cmd->input_fd = open(cmd->input_path, O_RDONLY | O_ASYNC);
	if (cmd->input_fd <= 0)
		str_error(app, cmd->name);
}
