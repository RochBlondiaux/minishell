/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:46:53 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*ft_env_new(char *content)
{
	t_env	*thelist;

	thelist = malloc(sizeof(t_env));
	if (!thelist)
		return (NULL);
	thelist->variable = content;
	thelist->next = NULL;
	return (thelist);
}

void	ft_env_add_back(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_list_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free(*env);
		*env = tmp;
	}
}

t_env	*list_env(char **env)
{
	size_t	i;
	t_env	*env_var;

	i = -1;
	env_var = NULL;
	while (env[++i])
	{
		ft_env_add_back(&env_var, ft_env_new(env[i]));
	}
	return (env_var);
}
