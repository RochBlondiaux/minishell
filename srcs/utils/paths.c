/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:04:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
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
	return (env("HOME"));
}

int	exists(char *path)
{
	DIR		*dir;

	if (!path)
		return (FALSE);
	dir = opendir(path);
	if (!dir)
		return (FALSE);
	closedir(dir);
	return (TRUE);
}

char	*parent(char *path)
{
	char	**a;
	char	*final;
	size_t	index;

	if (!exists(path))
		return (NULL);
	a = ft_split(path, '/');
	index = -1;
	final = ft_strdup("/");
	while (a[++index])
	{
		if (array_length(a) - 1 != index)
		{
			if (array_length(a) - 2 > index)
				final = ft_strjoin_properly(final,
						ft_strjoin_properly(a[index], ft_strdup("/")));
			else
				final = ft_strjoin_properly(final, a[index]);
		}
		else
			free (a[index]);
	}
	free(a);
	return (final);
}

char	*path(char *raw)
{
	char	*tmp;

	if (!raw)
		return (NULL);
	if (raw[ft_strlen(raw) - 1] != '/')
		tmp = ft_strjoin(raw, "/");
	else
		tmp = ft_strdup(raw);
	if (exists(tmp))
		return (tmp);
	tmp = ft_strjoin_properly(working_directory(), tmp);
	if (!exists(tmp))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
