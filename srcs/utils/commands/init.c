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
	cmd->args = empty_array();
	cmd->name = ft_strdup("");
	cmd->input = ft_strdup("");
	cmd->output = ft_strdup("");
	cmd->input_path = ft_strdup("");
	cmd->output_path = ft_strdup("");
	cmd->delimiter = FALSE;
	cmd->appender = FALSE;
	cmd->status = 0;
	return (cmd);
}
