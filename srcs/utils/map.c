/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:46:53 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_vars(char *entry)
{
	char	**e;
	t_env	*env;

	if (ft_strchr(entry, '=') <= 0)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	e = ft_split(entry, '=');
	env->key = ft_strdup(e[0]);
	if (array_length(e) >= 2)
		env->value = ft_strdup(e[1]);
	else
		env->value = ft_strdup(" ");
	env->next = NULL;
	free_array(e);
	return (env);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*init_env_map(char **env)
{
	size_t	i;
	t_env	*env_var;

	i = -1;
	env_var = NULL;
	while (env[++i])
		add_env(&env_var, create_env_vars(env[i]));
	return (env_var);
}

void	free_map(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}
