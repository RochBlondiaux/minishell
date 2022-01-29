/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programms.c                                        :+:      :+:    :+:   */
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

char	*get_program_path(char *name)
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
