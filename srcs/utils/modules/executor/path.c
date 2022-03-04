/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 10:14:26 by lfilloux         ###   ########.fr       */
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

static char	*exec_errors(t_app *app, t_command *cmd, char *tmp, char *input)
{
	if (input[0] == '.' && input[1] == '/')
	{
		cmd->status = 126;
		errno = 13;
		str_error(app, cmd->name);
	}
	else if (input[0] != '$')
	{
		cmd->status = 127;
		error(app, cmd->name, COMMAND_NOT_FOUND);
	}
	free(tmp);
	return (ft_strdup(""));
}

static char	*no_path(t_app *app, t_command *cmd)
{
	char	**split;
	size_t	j;

	cmd->status = 127;
	split = ft_split(cmd->name, '/');
	j = array_length(split) - 1;
	errno = 2;
	str_error(app, split[j]);
	return (ft_strdup(""));
}

char	*get_executable(t_app *app, t_command *cmd, char *input)
{
	char		**paths;
	int			i;
	char		*path;
	char		*tmp;

// CHANGER CA MARHCE PAS GENRE ./TEST = rien alors que ca devrait etre no 
//					such file or directory
	i = -1;
	if (get_env(app, "PATH") == NULL)
		return (no_path(app, cmd));
	if (access(input, F_OK) == FALSE)
		return (ft_strdup(input));
	paths = ft_split(get_env(app, "PATH"), ':');
	path = NULL;
	while (paths[++i])
	{
		tmp = get_accurate_path(paths[i], input);
		if (tmp && !path && access(tmp, F_OK) == FALSE)
			path = ft_strdup(tmp);
		else if (access(tmp, F_OK | X_OK) == 0)
		{
			free(path);
			free_array(paths);
			return (exec_errors(app, cmd, tmp, input));
		}
		free(tmp);
	}
	free_array(paths);
	return (path);
}
