/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:14:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	hande_command(t_app *app, char *name, char **args)
{
	if (ft_strcmp(name, "cd"))
		m_cd(app, args);
	else if (ft_strcmp(name, "pwd"))
		m_pwd(app, args);
	else if (ft_strcmp(name, "echo"))
		m_echo(args);
	else if (ft_strcmp(name, "export"))
		m_export(args);
	else if (ft_strcmp(name, "unset"))
		m_unset(args);
	else if (ft_strcmp(name, "env"))
		m_env(args);
	else if (ft_strcmp(name, "exit"))
		m_exit(app);
	else
		return (0);
	return (1);
}
