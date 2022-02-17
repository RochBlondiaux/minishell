/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                          :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup("");
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->input_path = ft_strdup("");
	cmd->output_path = ft_strdup("");
	cmd->delimiter = FALSE;
	cmd->appender = FALSE;
	cmd->previous_token = LITERAL;
	cmd->next_token = LITERAL;
	cmd->status = 0;
	return (cmd);
}
