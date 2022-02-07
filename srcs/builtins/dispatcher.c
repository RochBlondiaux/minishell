/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:14:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 14:41:51 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dispatch_builtin(t_app *app, t_command *command)
{
	char	*name;
	char	**args;

	args = command->args;
	printf("%s\n", args[0]);
	name = command->name;
	printf("%s\n", name);
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
