/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:14:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dispatch_builtin(t_app *app, t_command *command)
{
	char	*name;
	char	**args;

	args = command->args;
	name = command->name;
	if (ft_strcmp(name, "cd"))
		builtin_cd(app, args);
	else if (ft_strcmp(name, "pwd"))
		builtin_pwd(app);
	else if (ft_strcmp(name, "echo"))
		builtin_echo(args);
	else if (ft_strcmp(name, "export"))
		builtin_export(app, args);
	else if (ft_strcmp(name, "unset"))
		builtin_unset(app, args);
	else if (ft_strcmp(name, "env"))
		builtin_env(app);
	else if (ft_strcmp(name, "exit"))
		builtin_exit(app);
	else
		return (FALSE);
	return (TRUE);
}