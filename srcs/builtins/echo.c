/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_command *cmd)
{
	int		mode;
	size_t	i;

	i = 0;
	mode = 0;
	while (ft_strcmp_sensitive(cmd->args[i++], "-n"))
		mode = 1;
	i -= 2;
	while (cmd->args[++i])
	{
		if (i == array_length(cmd->args) - 1)
			printf("%s", cmd->args[i]);
		else
			printf("%s ", cmd->args[i]);
	}
	if (array_length(cmd->args) > 0)
	{
		if (mode)
			printf("%s%s%%%s", BOLD, "\033[3;107;30m", RESET);
		printf("\n");
	}
	else
		printf("\n");
	cmd->status = 0;
}
