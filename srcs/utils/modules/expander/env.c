/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	contains_envars(char *a)
{
	size_t	index;

	index = -1;
	while (a[++index])
	{
		if (a[index] == '$' && a[index + 1])
			return (1);
	}
	return (0);
}

static char	*get_env_string(char *src)
{
	int	index;

	index = ft_strchr(src, '$');
	if (index == -1)
		return (NULL);
	index++;
	while (src[index] && (ft_isalpha(src[index]) || (src[index] == '?'
				&& (!src[index + 1] || !ft_isalpha(src[index + 1])))))
		index++;
	return (ft_substr(src, ft_strchr(src, '$'), index));
}

void	expand_env_vars(t_app *app, t_command *cmd)
{
	int		index;
	char	*v;
	char	*env;

	index = -1;
	while (cmd->args[++index])
	{
		if (!contains_envars(cmd->args[index]))
			continue ;
		v = get_env_string(cmd->args[index]);
		if (!v)
			continue ;
		env = get_env(app, &v[1]);
		if (env)
			v = replace_str(cmd->args[index], v, ft_strdup(env));
		else
		{
			if (v[1] == '?')
				v = replace_str(cmd->args[index], v, ft_itoa(app->last_exit));
			else
				v = replace_str(cmd->args[index], v, ft_strdup(&v[0]));
		}
		reset_str(&cmd->args[index], v);
	}
}
