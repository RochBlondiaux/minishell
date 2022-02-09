/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:45:08 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env(char *name)
{
	char	*v;

	v = getenv(name);
	if (v == NULL)
		return (NULL);
	return (ft_strdup(v));
}

t_env	*get_env(t_env *env, char *key)
{
	t_env	*tmp;

	while (env)
	{
		tmp = (env)->next;
		if (tmp && ft_strcmp_sensitive(tmp->key, key))
			return (tmp);
		env = tmp;
	}
	return (NULL);
}

void	remove_env(t_app *app, t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	if (tmp != NULL && ft_strcmp_sensitive(tmp->key, key))
	{
		*env = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp && !ft_strcmp_sensitive(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		str_error(app, UNSET_ERROR);
		return ;
	}
	prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
