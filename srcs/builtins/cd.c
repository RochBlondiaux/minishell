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
	{
		if (!home_directory(app)[0])
			return (working_directory());
		return (home_directory(app));
	}
	if (ft_strcmp(input, "-"))
	{
		i = get_old_path(app);
		if (!i)
			return (NULL);
		printf("%s\n", i);
	}
	else
	{
		split = ft_split(input, '/');
		if (!split)
		{
			temp = ft_strjoin_properly(working_directory(), ft_strdup("/"));
			i = ft_strjoin_properly(temp, ft_strdup(input));
		}
		i = path(input);
		j = -1;
		if (i)
		{
			while (split[++j])
			{
				if (ft_strcmp(split[j], "."))
				{
					free(i);
					i = working_directory();
				}
				else if (ft_strcmp(split[j], ".."))
				{
					if (j == 0)
						temp = working_directory();
					else
						temp = ft_strdup(input);
					free(i);
					i = ft_substr(temp, 0, ft_strlen_lastrepo(temp));
					free (temp);
				}
				else
				{
					free(i);
					i = ft_strjoin_properly(working_directory(), ft_strjoin("/", split[j]));
				}
			}
			free_array(split);
		}
		else
		{
			free(i);
			i = ft_strdup(input);
			if (get_env(app, "CDPATH") && get_env(app, "CDPATH")[0])
			{
				while (split[++j])
				{
					if (ft_strcmp(split[j], "."))
					{
						free(i);
						i = working_directory() ;
					}
					else if (ft_strcmp(split[j], ".."))
					{
						if (j == 0)
							temp = working_directory();
						else
							temp = ft_strdup(i);
						free(i);
						i = ft_substr(temp, 0, ft_strlen_lastrepo(temp));
						free (temp);
					}
					else
					{
						if (j == 0)
						{
							free (i);
							i = ft_strjoin_properly(get_env(app, "CDPATH"), ft_strdup(split[j]));
						}
						else
						{
							temp = ft_strjoin_properly(i, ft_strdup("/"));
							i = ft_strjoin_properly(temp, ft_strdup(split[j]));
						}
					}
				}
				printf("%s\n", i);
			}
			free_array(split);
		}
	}
	return (i);
}

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
