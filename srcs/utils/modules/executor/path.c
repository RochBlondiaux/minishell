/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static char	*get_accurate_path(char *path, char *name)
{
	char	*final;
	char	*tmp;

	if (access(name, F_OK) == FALSE)
		return (ft_strdup(name));
	if (path[ft_strlen(path) - 1] != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	final = ft_strjoin(tmp, name);
	free(tmp);
	return (final);
}

char	*get_executable(t_app *app, t_command *cmd, char *input)
{
	char	**paths;
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	paths = ft_split(get_env(app, "PATH"), ':');
	path = NULL;
	while (paths[i])
	{
		tmp = get_accurate_path(paths[i], input);
		if (tmp && !path && access(tmp, F_OK) == FALSE)
			path = ft_strdup(tmp);
		free(tmp);
		free(paths[i]);
		i++;
	}
	free(paths);
	if(path && access(path, X_OK | F_OK) == FALSE)
		return (path);
	if (path[0] && path[1] && path[0] == '.' && path[1] == '/')
	{
		cmd->status = 126;
		error(app, input, "FUCK OFF!");
	}
	else
	{
		cmd->status = 127;
		error(app, input, "PAS UN EXECUTABLER!");
	}
	return (ft_strdup(""));
}
