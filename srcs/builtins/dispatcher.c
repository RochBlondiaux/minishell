/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dispatch_builtins(t_app *app, t_command *cmd)
{
	if (ft_strcmp(cmd->name, "cd"))
		builtin_cd(app, cmd);
	else if (ft_strcmp(cmd->name, "echo"))
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->name, "pwd"))
		builtin_pwd(app);
	else if (ft_strcmp(cmd->name, "exit"))
		builtin_exit(app);
	else if (ft_strcmp(cmd->name, "unset"))
		builtin_unset(app, cmd);
	else if (ft_strcmp(cmd->name, "export"))
		builtin_export(app, cmd);
	else if (ft_strcmp(cmd->name, "env"))
		builtin_env(app, cmd);
}
