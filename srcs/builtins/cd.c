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

static int	set_path(t_app *app, char *a)
{
	int	ret;

	set_env(app, "OLDPWD", get_env(app, "PWD"));
	set_env(app, "PWD", a);
	ret = chdir(a);
	free(a);
	return (ret == FALSE);
}

static char	*get_old_path(t_app *app)
{
	char	*old;

	old = get_env(app, "OLDPWD");
	if (!old)
	{
		error(app, "cd", OLDPWD_UNDEFINED);
		return (NULL);
	}
	return (ft_strdup(old));
}

static size_t	ft_strlen_lastrepo(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	while (--i > 0)
	{
		if (s[i] == '/')
			return (i);
	}
	return (1);
}

static char	*get_path(t_app *app, char *input)
{
	char	**split;
	char	*temp;
	char	*i;
	size_t	j;

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
	else
	{
		split = ft_split(i, '/');
		if (!split)
		{
			printf("test");
			temp = ft_strjoin_properly(working_directory(), ft_strdup("/"));
			i = ft_strjoin_properly(temp, i);
		}
		j = -1;
		while (split[++j])
		{
			if (ft_strcmp(split[j], ".."))
			{
				if (j == 0)
					temp = working_directory();
				else
					temp = ft_strdup(i);
				i = ft_substr(temp, 0, ft_strlen_lastrepo(temp));
			}
			else
			{
				temp = ft_strjoin(split[j], "/");
				i = ft_strjoin(ft_strjoin_properly(working_directory(), ft_strdup("/")), temp);
				if (!set_path(app, path(temp)))
					error(app, "cd", "TG");	
				free(temp);
			}
		}
		free_array(split);
	}
	return (i);
}

/*static int	check_existing_cdpath(t_app *app, char *dest, char **args, size_t i)
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
		if (!app->last_path[0])
			str_error(app, UNINITIALIZED);
		else
		{
			set_path(app, app->last_path);
			app->last_path = ft_strdup(current);
		}
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
*/

void	builtin_cd(t_app *app, t_command *cmd)
{
	char	*path;

	if (array_length(cmd->args) > 1)
	{
		error(app, "cd", TOO_MANY_ARGUMENTS);
		cmd->status = 1;
		return ;
	}
	path = get_path(app, cmd->args[0]);
	if (!path)
	{
		cmd->status = 1;
		return ;
	}
	if (!set_path(app, path))
	{
		str_error(app, "cd");
		cmd->status = 1;
		return ;
	}
	cmd->status = 0;
}
