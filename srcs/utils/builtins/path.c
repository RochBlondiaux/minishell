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

#include "../../../includes/minishell.h"

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

static char *cdpath_exist(t_app *app, char *input, char **split)
{
	size_t	j;
	char	*temp;

	j = -1;
	if (get_env(app, "CDPATH") && get_env(app, "CDPATH")[0])
	{
		while (split[++j])
		{
			if (ft_strcmp(split[j], "."))
			{
				free(input);
				input = working_directory();
			}
			else if (ft_strcmp(split[j], ".."))
			{
				if (j == 0)
					temp = working_directory();
				else
					temp = ft_strdup(input);
				free(input);
				input = ft_substr(temp, 0, ft_strlen_lastrepo(temp));
				free (temp);
			}
			else
			{
				if (j == 0)
				{
					free (input);
					input = ft_strjoin_properly(get_env(app, "CDPATH"),
					ft_strdup(split[j]));
				}
				else
				{
					temp = ft_strjoin_properly(input, ft_strdup("/"));
					input = ft_strjoin_properly(temp, ft_strdup(split[j]));
				}
			}
		}
		printf("%s\n", input);
	}
	free_array(split);
	return (input);
}

static char	*is_a_path(char *input, char **split)
{
	size_t	j;
	char	*temp;
	char	*tmp;

	j = -1;
	tmp = ft_strdup(input);
	while (split[++j])
	{
		if (ft_strcmp(split[j], "."))
		{
			free(input);
			input = working_directory();
		}
		else if (ft_strcmp(split[j], ".."))
		{
			if (j == 0)
				temp = working_directory();
			else
				temp = ft_strdup(input);
			free(input);
			input = ft_substr(temp, 0, ft_strlen_lastrepo(temp));
			free (temp);
		}
		else
		{
			free(input);
			input = ft_strjoin_properly(working_directory(),
			ft_strjoin("/", split[j]));
			}
		}
		temp = path(input);
		if (!path(temp))
			reset_str(&input, ft_strdup(tmp));
	free(tmp);
	free_array(split);
	return (input);
}

char	*get_path(t_app *app, char *input)
{
	char	**split;
	char	*temp;
	char	*i;

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
		if (i)
			i = is_a_path(i, split);
		else
		{
			free(i);
			i = ft_strdup(input);
			i = cdpath_exist(app, i, split);
		}
	}
	return (i);
}
