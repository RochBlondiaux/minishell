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

static int	contains_envars(t_app *app, char *a)
{
	size_t	index;
	char	*s;

	index = -1;
	while (a[++index])
	{
		if (a[index] == '$' && a[index + 1])
		{
			if (a[index + 1] == '?' && (!a[index + 2] || a[index + 2] == ' '))
				return (1);
			s = get_env(app, &a[index + 1]);
			if (!s)
				continue ;
			return (1);
		}
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

static void expand_single(t_app *app, char **string)
{
	char	*v;
	char	*env;

	if (!contains_envars(app, *string))
		return ;
	v = get_env_string(*string);
	if (!v)
		return ;
	env = get_env(app, &v[1]);
	if (!env && v[1] != '?')
		return;
	if (v[1] == '?')
		v = replace_str(*string, v, ft_itoa(app->last_exit));
	else
		v = replace_str(*string, v, ft_strdup(env));
	reset_str(string, ft_strdup(v));
}

void	expand_env_vars(t_app *app, char **input)
{
		expand_single(app, input);
}
