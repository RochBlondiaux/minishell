/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void set_path(t_app *app, char *a)
{
	set_env(app, "OLDPWD", get_env(app, "PWD"));
	set_env(app, "PWD", a);
	free(a);
}

static char	*get_old_path(t_app *app)
{
	char	*old;

	old = get_env(app, "OLDPWD");
	if (!old)
	{
		error(app, "cd", "OLDPWD not set");
		return (NULL);
	}
	return (ft_strdup(old));
}

static char	*get_path(t_app *app, char *input)
{
	char	*path;
	char	*i;

	if (!input)
		return (home_directory(app));
	i = ft_strdup(input);
	if (ft_strcmp(i, "-"))
	{
		free(i);
		i = get_old_path(app);
		if (!i)
			return (NULL);
	}
	else if (is_relative(i))
	{
		path = ft_strjoin_properly(working_directory(), ft_strdup("/"));
		i = ft_strjoin_properly(path, i);
	}
	return (i);
}

void	builtin_cd(t_app *app, t_command *cmd)
{
	char	*path;

	if (array_length(cmd->args) > 1)
	{
		error(app, "cd", "Too many arguments");
		cmd->status = 1;
		return ;
	}
	path = get_path(app, cmd->args[0]);
	if (!path)
	{
		cmd->status = 1;
		return ;
	}
	set_path(app, path);
	cmd->status = 0;
}
