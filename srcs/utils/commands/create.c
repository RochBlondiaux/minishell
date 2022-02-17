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

t_command	*create_command(char **args)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(args[0]);
	cmd->args = sub_array(args, 1, array_length(args));
	cmd->input_fd = 0;
	cmd->output_fd = 0;
	cmd->input_path = ft_strdup("");
	cmd->output_path = ft_strdup("");
	cmd->delimiter = FALSE;
	cmd->appender = FALSE;
	cmd->status = 0;
	free_array(args);
	return (cmd);
}
