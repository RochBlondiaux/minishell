/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:54 by rblondia          #+#    #+#             */
/*   Updated: 2022/02/07 17:37:38 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_existing_cdpath(t_app *app, char *dest, char **args, size_t i)
{
	char	*temp;

	if (ft_strncmp(dest, "/", 1) && ft_strncmp(args[0], "/", 1) == 0 && i == 0)
		{
			temp = ft_strjoin("/", dest);
			if (!set_path(app, path(temp)))
			{
				error(app, ENOENT);
				return (-1);
			}
			free(temp);
		}
	else
	{
		if (!set_path(app, path(dest)))
		{
			error(app, ENOENT);
			return (-1);
		}
	}
	return (0);
}

static int	check_existing_cd(t_app *app, char *dest, char **args, size_t i)
{
	if (ft_strcmp(dest, ".."))
	{
		if (!set_path(app, parent(working_directory())))
		{
			error(app, ENOENT);
			return (-1);
		}
	}
	else
		if (check_existing_cdpath(app, dest, args, i) != 0)
			return (-1);
	return (0);
}

static int	special_cd_path(t_app *app, char **args, char *current)
{
	if (ft_strcmp(args[0], "/"))
	{
		set_path(app, ft_strdup("/"));
		return (0);
	}
	else if (ft_strcmp(args[0], "-"))
	{
		set_path(app, app->last_path);
		app->last_path = ft_strdup(current);
		free(current);
		return (0);
	}
	return (1);
}

void	builtin_cd(t_app *app, char **args)
{
	char	**dest;
	char	*current;
	size_t	i;

	current = working_directory();
	if (array_length(args) == 0)
		set_path(app, home_directory());
	else if (array_length(args) == 1)
	{
		if (special_cd_path(app, args, current) == 0)
			return ;
		i = -1;
		dest = ft_split(args[0], '/');
		while (dest[++i])
			if (check_existing_cd(app, dest[i], args, i) != 0)
				break ;
		free_array(dest);
	}
	else
		str_error(app, TOO_MANY_ARGUMENTS);
	free(app->last_path);
	app->last_path = ft_strdup(current);
	free(current);
}
