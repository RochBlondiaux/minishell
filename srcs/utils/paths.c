/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:04:33 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 17:36:58 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*working_directory(void)
{
	char	cwd[1024];

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
	free(path);
	free(a);
	return (final);
}

char	*path(char *raw)
{
	char	*tmp;
	char	*temp;

	if (!raw)
		return (NULL);
	else if (raw[ft_strlen(raw) - 1] != '/')
		temp = ft_strjoin(raw, "/");
	else
		temp = ft_strdup(raw);
	if (exists(temp) && raw[0] == '/')
		return (temp);
	tmp = ft_strjoin_properly(working_directory(), ft_strdup("/"));
	tmp = ft_strjoin_properly(tmp, temp);
	if (!exists(tmp))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
