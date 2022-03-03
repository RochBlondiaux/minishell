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

static char	*right_dir(t_app *app)
{
	if (!home_directory(app)[0])
			return (working_directory());
		return (home_directory(app));
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

static char	*get_new_path(char *input, char *arg)
{
	char	*temp;
 
	temp = ft_strjoin_properly(input, ft_strdup("/"));
	input = ft_strjoin_properly(temp, ft_strdup(arg));
	return (input);
}

static char	*chose_cdpath(t_app *app, char *input, char * arg)
{
	free(input);
	input = ft_strjoin_properly(get_env(app, "CDPATH"), ft_strdup(arg));
	return (input);
}

static char	*chose_path(t_app *app, char *input, char **split)
{
	size_t	j;
	char	*temp;
 
	j = -1;
	while (split[++j])
	{
		if (ft_strcmp(split[j], "."))
			reset_str(&input, working_directory());
		else if (ft_strcmp(split[j], ".."))
		{
			if (j == 0)
				temp = working_directory();
			else
				temp = ft_strdup(input);
			reset_str(&input, ft_substr(temp, 0, ft_strlen_lastrepo(temp)));
			free (temp);
		}
		else
			if (j == 0)
				input = chose_cdpath(app, input, split[j]);
			else
				input = get_new_path(input, split[j]);
	}
	printf("%s\n", input);
	return (input);
}

static char *cdpath_exist(t_app *app, char *input, char **split)
{
	if (get_env(app, "CDPATH") && get_env(app, "CDPATH")[0])
		input = chose_path(app, input, split);
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
			reset_str(&input, working_directory());
		else if (ft_strcmp(split[j], ".."))
		{
			if (j == 0)
				temp = working_directory();
			else
				temp = ft_strdup(input);
			reset_str(&input, ft_substr(temp, 0, ft_strlen_lastrepo(temp)));
			free (temp);
		}
		else
		{
			free(input);
			input = ft_strjoin_properly(working_directory(),
			ft_strjoin("/", split[j]));
		}
		temp = strdup(input);
		if (!temp)
			reset_str(&input, ft_strdup(tmp));
		free(temp);
	}
	free(tmp);
	free_array(split);
	return (input);
}

char	*get_path(t_app *app, char *input)
{
	char	**split;
	char	*i;
 
	if (!input)
		return(right_dir(app));
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
			i = get_new_path(working_directory(), input);
		i = path(input);
		if (i)
			i = is_a_path(i, split);
		else
			reset_str(&i, cdpath_exist(app, ft_strdup(input), split));
	}
	return (i);
}
