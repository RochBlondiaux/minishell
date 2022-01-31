/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:46:53 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_accurate_path(char *path, char *name)
{
	char	*final;
	char	*tmp;

	if (path[ft_strlen(path) - 1] != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	final = ft_strjoin(tmp, name);
	free(tmp);
	return (final);
}

char	*get_command_path(char *name)
{
	char	**paths;
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	path = NULL;
	while (paths[i])
	{
		tmp = get_accurate_path(paths[i], name);
		if (tmp && access(tmp, X_OK) == FALSE)
			path = ft_strdup(tmp);
		free(tmp);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (path);
}

void	free_native_cmd(t_native *cmd)
{
	free(cmd->output);
	free(cmd->args);
	free(cmd->name);
	free(cmd);
}

t_native	*create_native_cmd(t_command *cmd)
{
	t_native	*native;

	native = malloc(sizeof(t_native));
	if (!native)
		return (NULL);
	native->command = cmd;
	native->exit = -1;
	native->pid = fork();
	native->args = add_array_element(cmd->args, cmd->name);
	native->name = get_command_path(cmd->name);
	native->output = ft_strdup("");
	return (native);
}
