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
	char		**paths;
	int			i;
	char		*path;
	char		*tmp;

	i = 0;
	if (get_env(app, "PATH") == NULL)
		return (ft_strdup(""));
	paths = ft_split(get_env(app, "PATH"), ':');
	path = NULL;
	while (paths[i])
	{
		tmp = get_accurate_path(paths[i], input);
		if (tmp && !path && access(tmp, F_OK) == FALSE)
			path = ft_strdup(tmp);
		else
		{
			if (access(tmp, F_OK | X_OK) == 0)
			{
				if (input[0] == '.' && input[1] == '/')
				{
					cmd->status = 126;
					errno = 13;
					str_error(app, cmd->name);
				}
				else
				{
					cmd->status = 127;
					error(app, cmd->name, COMMAND_NOT_FOUND);
				}
				free(tmp);
				free(path);
				free_array(paths);
				return (ft_strdup(""));
			}
		}
		free(tmp);
		i++;
	}
	free_array(paths);
	return (path);
}
