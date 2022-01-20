/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:04:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/20 23:02:55 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*working_directory(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup(cwd));
	return (NULL);
}

char	*home_directory(void)
{
	char	*dir;

	dir = getenv("HOME");
	if (dir == NULL)
		return (NULL);
	return (ft_strdup(dir));
}

char	*path(char *raw)
{
	DIR		*dir;
	char	*tmp;

	if (!raw)
		return (NULL);
	dir = opendir(raw);
	if (!dir)
		return (NULL);
	closedir(dir);
	tmp = ft_strjoin("/", raw);
	return (ft_strjoin_properly(working_directory(), tmp));
}
